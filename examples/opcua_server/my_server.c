/* WARNING: This is a generated file.
 * Any manual changes will be overwritten. */

#include "my_server.h"

/* Main Structure - ns=1;i=2001 */

static UA_StatusCode function_my_server_0_begin(UA_Server *server, UA_UInt16 *ns)
{
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    UA_ObjectAttributes attr = UA_ObjectAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("", "Main Structure");
    retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECT,
                                      UA_NODEID_NUMERIC(ns[1], 2001LU),
                                      UA_NODEID_NUMERIC(ns[0], 85LU),
                                      UA_NODEID_NUMERIC(ns[0], 35LU),
                                      UA_QUALIFIEDNAME(ns[1], "Main Structure"),
                                      UA_NODEID_NUMERIC(ns[0], 58LU),
                                      (const UA_NodeAttributes *)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES], NULL, NULL);
    if (retVal != UA_STATUSCODE_GOOD)
        return retVal;
    return retVal;
}

static UA_StatusCode function_my_server_0_finish(UA_Server *server, UA_UInt16 *ns)
{
    return UA_Server_addNode_finish(server,
                                    UA_NODEID_NUMERIC(ns[1], 2001LU));
}

/* Data - ns=1;i=2004 */

static UA_StatusCode function_my_server_1_begin(UA_Server *server, UA_UInt16 *ns)
{
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.minimumSamplingInterval = 0.000000;
    attr.userAccessLevel = 3;
    attr.accessLevel = 3;
    /* Value rank inherited */
    attr.valueRank = -2;
    attr.dataType = UA_NODEID_NUMERIC(ns[0], 12877LU);
    attr.displayName = UA_LOCALIZEDTEXT("", "Data");
#ifdef UA_ENABLE_NODESET_COMPILER_DESCRIPTIONS
    attr.description = UA_LOCALIZEDTEXT("", "Data");
#endif
    retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
                                      UA_NODEID_NUMERIC(ns[1], 2004LU),
                                      UA_NODEID_NUMERIC(ns[1], 2001LU),
                                      UA_NODEID_NUMERIC(ns[0], 47LU),
                                      UA_QUALIFIEDNAME(ns[1], "Data"),
                                      UA_NODEID_NUMERIC(ns[0], 63LU),
                                      (const UA_NodeAttributes *)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES], NULL, NULL);
    if (retVal != UA_STATUSCODE_GOOD)
        return retVal;
    return retVal;
}

static UA_StatusCode function_my_server_1_finish(UA_Server *server, UA_UInt16 *ns)
{
    return UA_Server_addNode_finish(server,
                                    UA_NODEID_NUMERIC(ns[1], 2004LU));
}

/* Message Counter - ns=1;i=2003 */

static UA_StatusCode function_my_server_2_begin(UA_Server *server, UA_UInt16 *ns)
{
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.minimumSamplingInterval = 0.000000;
    attr.userAccessLevel = 3;
    attr.accessLevel = 3;
    /* Value rank inherited */
    attr.valueRank = -2;
    attr.dataType = UA_NODEID_NUMERIC(ns[0], 12877LU);
    attr.displayName = UA_LOCALIZEDTEXT("", "Message Counter");
#ifdef UA_ENABLE_NODESET_COMPILER_DESCRIPTIONS
    attr.description = UA_LOCALIZEDTEXT("", "Message Counter");
#endif
    retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
                                      UA_NODEID_NUMERIC(ns[1], 2003LU),
                                      UA_NODEID_NUMERIC(ns[1], 2001LU),
                                      UA_NODEID_NUMERIC(ns[0], 47LU),
                                      UA_QUALIFIEDNAME(ns[1], "Message Counter"),
                                      UA_NODEID_NUMERIC(ns[0], 63LU),
                                      (const UA_NodeAttributes *)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES], NULL, NULL);
    if (retVal != UA_STATUSCODE_GOOD)
        return retVal;
    return retVal;
}

static UA_StatusCode function_my_server_2_finish(UA_Server *server, UA_UInt16 *ns)
{
    return UA_Server_addNode_finish(server,
                                    UA_NODEID_NUMERIC(ns[1], 2003LU));
}

/* Message Type - ns=1;i=2002 */

static UA_StatusCode function_my_server_3_begin(UA_Server *server, UA_UInt16 *ns)
{
    int value = 15;
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.minimumSamplingInterval = 0.000000;
    attr.userAccessLevel = 3;
    attr.accessLevel = 3;
    /* Value rank inherited */
    attr.valueRank = -2;
    attr.dataType = UA_NODEID_NUMERIC(ns[0], 12877LU);
    attr.displayName = UA_LOCALIZEDTEXT("", "Message Type");
#ifdef UA_ENABLE_NODESET_COMPILER_DESCRIPTIONS
    attr.description = UA_LOCALIZEDTEXT("", "Message Type");
#endif
    retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
                                      UA_NODEID_NUMERIC(ns[1], 2002LU),
                                      UA_NODEID_NUMERIC(ns[1], 2001LU),
                                      UA_NODEID_NUMERIC(ns[0], 47LU),
                                      UA_QUALIFIEDNAME(ns[1], "Message Type"),
                                      UA_NODEID_NUMERIC(ns[0], 63LU),
                                      (const UA_NodeAttributes *)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES], NULL, NULL);
    if (retVal != UA_STATUSCODE_GOOD)
        return retVal;
    return retVal;
}

static UA_StatusCode function_my_server_3_finish(UA_Server *server, UA_UInt16 *ns)
{
    return UA_Server_addNode_finish(server,
                                    UA_NODEID_NUMERIC(ns[1], 2002LU));
}

UA_StatusCode my_server(UA_Server *server)
{
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    /* Use namespace ids generated by the server */
    UA_UInt16 ns[2];
    ns[0] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/");
    ns[1] = UA_Server_addNamespace(server, "http//freeopcua/defaults/modeler");

    /* Load custom datatype definitions into the server */
    if ((retVal = function_my_server_0_begin(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_1_begin(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_2_begin(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_3_begin(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_3_finish(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_2_finish(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_1_finish(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    if ((retVal = function_my_server_0_finish(server, ns)) != UA_STATUSCODE_GOOD)
        return retVal;
    return retVal;
}
