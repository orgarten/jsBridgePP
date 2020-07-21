add_executable(jsBridge++_server main.cpp)
set_target_properties(jsBridge++_server PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(jsBridge++_server PUBLIC ${CMAKE_SOURCE_DIR}/jsBridge++/lib)