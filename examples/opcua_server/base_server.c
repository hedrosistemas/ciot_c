
#include "my_server.h"


UA_Boolean running = true;
void signalHandler(int sig) {
    running = false;
}

int main(int argc, char** argv)
{

    // Create a server listening on port 4840
    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

	UA_StatusCode retval = my_server(server);
	if(retval != UA_STATUSCODE_GOOD){
		printf("ERROR, could not add custome server's structure \n");
		UA_Server_delete(server);
		return -1;
	}
	
	retval = UA_Server_run(server, &running);
    // Run the server loop 
    UA_StatusCode status = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return status;
   

}
