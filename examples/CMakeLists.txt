
add_executable(hello hello.cpp)
target_link_libraries(hello PRIVATE Boost::async fmt::fmt)
