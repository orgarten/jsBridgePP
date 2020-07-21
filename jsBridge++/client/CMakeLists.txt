add_executable(jsBridge++_client main.cpp)
set_target_properties(jsBridge++_client  PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(jsBridge++_client PUBLIC ${CMAKE_SOURCE_DIR}/jsBridge++/lib)