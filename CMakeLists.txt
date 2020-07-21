CMAKE_MINIMUM_REQUIRED(VERSION 3.11.0)
PROJECT(jsBridge++)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

###################################################################
# define options which can be set by user
###################################################################

include(cmake/cache_options.cmake)

###################################################################
# Setting compiler flags regarding optimization etc for gcc, msvc, clang
###################################################################
# Compiler Flags
set(CMAKE_CXX_STANDARD 17)
IF (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++17 -O3 -Wall -fPIC -funroll-loops -march=native)
ELSEIF (MSVC)
    # this currently works, but is not really the way to go..
    add_compile_options(/std:c++17 /Wall /arch:AVX)
ELSE ()
    add_compile_options(-std=c++17 -O3 -Wall -fPIC -funroll-loops -march=native)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)


## Allows us the check whether a compiler accepts flags or not
INCLUDE(CheckCXXCompilerFlag)
## loads definitions for standard gnu install directories
INCLUDE(GNUInstallDirs)

###################################################################
# add server and client libs to  CMakeLists.txt
###################################################################
add_subdirectory(jsBridge++)

###################################################################
# add server and client applications
###################################################################
add_subdirectory(apps)

###################################################################
# Option dependent builds (e.g. testing, benchmarks, ...)
###################################################################

add_subdirectory(tests)

###################################################################
# PACKAGING (create config files)
###################################################################

SET(JSBRIDGEPP_VERSION_NUMBER 1.0.0)
SET(JSBRIDGEPP_VERSION_STRING ${JSBRIDGEPP_VERSION_NUMBER})
SET(JSBRIDGEPP_DEFINITIONS "")
SET(JSBRIDGEPP_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
SET(JSBRIDGEPP_ROOT_DIR ${CMAKE_INSTALL_PREFIX})

INCLUDE(CMakePackageConfigHelpers)

CONFIGURE_PACKAGE_CONFIG_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/jsBridgePP.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/jsBridgePPConfig.cmake
        PATH_VARS JSBRIDGEPP_INCLUDE_DIR JSBRIDGEPP_ROOT_DIR
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/jsBridgePP/cmake
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

WRITE_BASIC_PACKAGE_VERSION_FILE(jsBridgePPConfigVersion.cmake VERSION ${JSBRIDGEPP_VERSION_NUMBER} COMPATIBILITY SameMajorVersion)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/jsBridgePPConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/jsBridgePPConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_DATADIR}/jsBridgePP/cmake)
INSTALL(DIRECTORY jsBridgePP DESTINATION include)


