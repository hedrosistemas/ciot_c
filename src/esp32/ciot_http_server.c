/**
 * @file ciot_http_server.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_http_server.h"
#include "esp_http_server.h"
#include <freertos/timers.h>

#define CIOT_HTTP_SERVER_TIMEOUT_MS 15000

struct ciot_http_server
{
    ciot_http_server_base_t base;
    httpd_handle_t handle;
    httpd_req_t *req;
    TimerHandle_t timer;
};

static const char *TAG = "ciot_http_server";

static ciot_err_t ciot_https_register_routes(ciot_http_server_t self);
static esp_err_t ciot_post_handler(httpd_req_t *req);
static esp_err_t ciot_file_handler(httpd_req_t *req);
static const char *get_mime_type(const char *filename);
static void ciot_timeout_callback(TimerHandle_t xTimer);

ciot_http_server_t ciot_http_server_new(void *handle)
{
    ciot_http_server_t self = calloc(1, sizeof(struct ciot_http_server));
    ciot_http_server_init(self);

    self->timer = xTimerCreate(
        "ciot_http_server_timeout", 
        pdMS_TO_TICKS(CIOT_HTTP_SERVER_TIMEOUT_MS),
        pdFALSE,
        self,
        ciot_timeout_callback
    );
    if(self->timer == NULL)
    {
        CIOT_LOGE(TAG, "Error creating timer");
    }

    return self;
}

ciot_err_t ciot_http_server_start(ciot_http_server_t self, ciot_http_server_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_http_server_base_t *base = &self->base;

    base->cfg = *cfg;

    httpd_config_t httpd_config = HTTPD_DEFAULT_CONFIG();
    httpd_config.server_port = cfg->port;
    httpd_config.uri_match_fn = httpd_uri_match_wildcard;
    httpd_config.max_uri_handlers = 2;
    httpd_config.stack_size = 8192;

    esp_err_t err_code = httpd_start(&self->handle, &httpd_config);
    if (err_code == ESP_OK)
    {
        ESP_LOGI(TAG, "Server Started on port %lu", cfg->port);
        base->cfg = *cfg;
        ciot_https_register_routes(self);
        ciot_iface_send_event_type(&base->iface, CIOT_EVENT_TYPE_STARTED);
    }

    return err_code;
}

ciot_err_t ciot_http_server_stop(ciot_http_server_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return httpd_stop(self->handle);
}

ciot_err_t ciot_http_server_send_bytes(ciot_http_server_t self, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(data);
    httpd_resp_set_status(self->req, HTTPD_200);
    httpd_resp_set_type(self->req, HTTPD_TYPE_OCTET);
    httpd_resp_send(self->req, (const char*)data, size);
    if(self->req != NULL)
    {
        httpd_req_async_handler_complete(self->req);
        self->req = NULL;
    }
    xTimerStop(self->timer, 0);
    return CIOT_ERR_OK;
}

static ciot_err_t ciot_https_register_routes(ciot_http_server_t self)
{
    CIOT_LOGI(TAG, "Registering route: %s", self->base.cfg.route);
    httpd_uri_t post_uri = {
        .uri = self->base.cfg.route,
        .handler = ciot_post_handler,
        .method = HTTP_POST,
        .user_ctx = self,
    };
    esp_err_t err = httpd_register_uri_handler(self->handle, &post_uri);
    if(err) {
        CIOT_LOGE(TAG, "Register uri error: %s", esp_err_to_name(err));
        return CIOT_ERR_FAIL;
    }

    httpd_uri_t file_uri = {
        .uri = "/*", // Captura todas as URIs
        .method = HTTP_GET,
        .handler = ciot_file_handler,
        .user_ctx = NULL
    };
    err = httpd_register_uri_handler(self->handle, &file_uri);
    if(err) {
        CIOT_LOGE(TAG, "Register uri error: %s", esp_err_to_name(err));
        return CIOT_ERR_FAIL;
    }
    return CIOT_ERR_OK;
}

static esp_err_t ciot_post_handler(httpd_req_t *req)
{
    ciot_http_server_t self = (ciot_http_server_t)req->user_ctx;
    ciot_event_t event = { 0 };

    httpd_req_async_handler_begin(req, &self->req);

    event.type = CIOT_EVENT_TYPE_REQUEST;
    httpd_req_recv(req, (char*)event.raw.bytes, req->content_len);
    event.raw.size = req->content_len;
    ciot_iface_send_event(&self->base.iface, &event);

    if(self->timer != NULL)
    {
        if (xTimerStart(self->timer, 0) != pdPASS) {
            CIOT_LOGE(TAG, "Failed to start timer for request timeout");
        }
    }

    return CIOT_ERR_OK;
}

static esp_err_t ciot_file_handler(httpd_req_t *req)
{
    char filepath[36];
    snprintf(filepath, sizeof(filepath), "/fs%.*s", (int)(sizeof(filepath) - 4), req->uri);

    // Verificar se a URI é "/", servir "index.html"
    if (strcmp(req->uri, "/") == 0) {
        strcpy(filepath, "/fs/index.html");
    }

    // Buffer para armazenar o valor do cabeçalho "Accept-Encoding"
    char accept_encoding[16] = {0};
    httpd_req_get_hdr_value_str(req, "Accept-Encoding", accept_encoding, sizeof(accept_encoding));

    // Verificar suporte a gzip
    bool supports_gzip = strstr(accept_encoding, "gzip") != NULL;

    // Modificar o caminho para tentar servir o arquivo gzip, se suportado
    if (supports_gzip) {
        char gz_filepath[39];
        snprintf(gz_filepath, sizeof(gz_filepath), "%s.gz", filepath);
        FILE* gz_file = fopen(gz_filepath, "r");
        if (gz_file) {
            ESP_LOGI(TAG, "Serving gzip file: %s", gz_filepath);
            httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
            strcpy(filepath, gz_filepath); // Atualizar para o arquivo gzip
            fclose(gz_file); // Fechar para reabrir na leitura abaixo
        }
    }

    // Abrir o arquivo solicitado
    FILE* file = fopen(filepath, "r");
    if (!file) {
        ESP_LOGE(TAG, "Failed to open file: %s", filepath);
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Configurar o cabeçalho com o tipo de conteúdo adequado
    httpd_resp_set_type(req, get_mime_type(filepath));

    // Ler o arquivo e enviar seu conteúdo
    char buffer[128];
    size_t read_bytes;
    while ((read_bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (httpd_resp_send_chunk(req, buffer, read_bytes) != ESP_OK) {
            fclose(file);
            return ESP_FAIL;
        }
    }

    // Enviar a resposta final
    httpd_resp_send_chunk(req, NULL, 0);

    fclose(file);
    return ESP_OK;
}

static const char *get_mime_type(const char *filename)
{
    if (strstr(filename, ".html")) return "text/html";
    if (strstr(filename, ".css"))  return "text/css";
    if (strstr(filename, ".js"))   return "application/javascript";
    if (strstr(filename, ".png"))  return "image/png";
    if (strstr(filename, ".jpg"))  return "image/jpeg";
    if (strstr(filename, ".ico"))  return "image/x-icon";
    if (strstr(filename, ".svg"))  return "image/svg+xml";
    return "text/plain";
}

static void ciot_timeout_callback(TimerHandle_t xTimer)
{
    ciot_http_server_t self = pvTimerGetTimerID(xTimer);
    if(self->req != NULL)
    {
        CIOT_LOGE(TAG, "timeout!");
        httpd_req_async_handler_complete(self->req);
        self->req = NULL;
    }
}
