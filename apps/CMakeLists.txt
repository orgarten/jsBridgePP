IF(BUILD_SERVER)
    add_subdirectory(bridge)
ENDIF()

IF(BUILD_CLIENT)
    add_subdirectory(client)
ENDIF()
