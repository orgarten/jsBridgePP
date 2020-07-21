IF(BUILD_SERVER)
    add_subdirectory(server)
ENDIF()

IF(BUILD_CLIENT)
    add_subdirectory(client)
ENDIF()
