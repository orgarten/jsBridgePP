add_executable(jsBridge++_bridge main.cpp)
set_target_properties(jsBridge++_bridge PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(jsBridge++_bridge PUBLIC ${CMAKE_SOURCE_DIR}/jsBridge++ /usr/include)
target_link_libraries(jsBridge++_bridge -lpthread)