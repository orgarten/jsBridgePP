
IF(BUILD_SERVER)
    add_subdirectory(server)
ENDIF()

IF(BUILD_CLIENT)
    add_subdirectory(client)
ENDIF()

add_library(bridge_lib lib/server/Server.cpp lib/client/Client.cpp)