/**
 * @file ciot_crypt_test.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h>

#include "unity.h"
#include "ciot_crypt.h"

#define CIOT_CRYPT_INVALID_KEY (uint8_t*) "12345678"
#define CIOT_CRYPT_INVALID_KEY_SIZE 8

#define CIOT_CRYPT_VALID_KEY (uint8_t*) "1234567891234567"
#define CIOT_CRYPT_VALID_KEY_SIZE 16

#define CIOT_CRYPT_DATA_DECRYPTED "data_test"
#define CIOT_CRYPT_DATA_ENCRYPTED "v6PcItCKYZersU+bnAo1CA=="

void test_ciot_crypt_enc_null_crypt(void)
{
    char *data = CIOT_CRYPT_DATA_DECRYPTED;
    char out[32];
    ciot_err_t err = ciot_crypt_enc(NULL, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_enc_null_data(void)
{
    char out[32];
    ciot_crypt_t crypt = { 0 };
    ciot_err_t err = ciot_crypt_enc(&crypt, NULL, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_enc_null_buffer(void)
{
    char *data = CIOT_CRYPT_DATA_DECRYPTED;
    ciot_crypt_t crypt = { 0 };
    ciot_err_t err = ciot_crypt_enc(&crypt, data, NULL, 0);
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_enc_invalid_key_size(void)
{
    char out[32];
    char *data = CIOT_CRYPT_DATA_DECRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_INVALID_KEY,
        .key.size = CIOT_CRYPT_INVALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_enc(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__INVALID_KEY_SIZE);
}

void test_ciot_crypt_enc_invalid_size(void)
{
    char out[5];
    char *data = CIOT_CRYPT_DATA_DECRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_VALID_KEY,
        .key.size = CIOT_CRYPT_VALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_enc(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__INVALID_SIZE);
}

void test_ciot_crypt_enc_ok(void)
{
    char out[32];
    char *data = CIOT_CRYPT_DATA_DECRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_VALID_KEY,
        .key.size = CIOT_CRYPT_VALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_enc(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__OK);
    TEST_ASSERT(strcmp(out, CIOT_CRYPT_DATA_ENCRYPTED) == 0);
}

void test_ciot_crypt_dec_null_crypt(void)
{
    char *data = CIOT_CRYPT_DATA_ENCRYPTED;
    char out[32];
    ciot_err_t err = ciot_crypt_dec(NULL, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_dec_null_data(void)
{
    char out[32];
    ciot_crypt_t crypt = { 0 };
    ciot_err_t err = ciot_crypt_dec(&crypt, NULL, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_dec_null_buffer(void)
{
    char *data = CIOT_CRYPT_DATA_ENCRYPTED;
    ciot_crypt_t crypt = { 0 };
    ciot_err_t err = ciot_crypt_dec(&crypt, data, NULL, 0);
    TEST_ASSERT(err == CIOT_ERR__NULL_ARG);
}

void test_ciot_crypt_dec_invalid_key_size(void)
{
    char out[32];
    char *data = CIOT_CRYPT_DATA_ENCRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_INVALID_KEY,
        .key.size = CIOT_CRYPT_INVALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_dec(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__INVALID_KEY_SIZE);
}

void test_ciot_crypt_dec_invalid_size(void)
{
    char out[5];
    char *data = CIOT_CRYPT_DATA_ENCRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_VALID_KEY,
        .key.size = CIOT_CRYPT_VALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_dec(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__INVALID_SIZE);
}

void test_ciot_crypt_dec_ok(void)
{
    char out[32];
    char *data = CIOT_CRYPT_DATA_ENCRYPTED;
    ciot_crypt_t crypt = {
        .key.data = CIOT_CRYPT_VALID_KEY,
        .key.size = CIOT_CRYPT_VALID_KEY_SIZE,
    };
    ciot_err_t err = ciot_crypt_dec(&crypt, data, out, sizeof(out));
    TEST_ASSERT(err == CIOT_ERR__OK);
    TEST_ASSERT(strcmp(out, CIOT_CRYPT_DATA_DECRYPTED) == 0);
}

void test_ciot_crypt(void)
{
    RUN_TEST(test_ciot_crypt_enc_null_crypt);
    RUN_TEST(test_ciot_crypt_enc_null_data);
    RUN_TEST(test_ciot_crypt_enc_null_buffer);
    RUN_TEST(test_ciot_crypt_enc_invalid_key_size);
    RUN_TEST(test_ciot_crypt_enc_invalid_size);
    RUN_TEST(test_ciot_crypt_enc_ok);

    RUN_TEST(test_ciot_crypt_dec_null_crypt);
    RUN_TEST(test_ciot_crypt_dec_null_data);
    RUN_TEST(test_ciot_crypt_dec_null_buffer);
    RUN_TEST(test_ciot_crypt_dec_invalid_key_size);
    RUN_TEST(test_ciot_crypt_dec_invalid_size);
    RUN_TEST(test_ciot_crypt_dec_ok);
}
