cmake_minimum_required(VERSION 3.20)
project(boost-async-playground CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -fdiagnostics-color=always)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------
# Third-party libraries
# --------------------------------------------------

add_subdirectory(fmt)

set(BOOST_INCLUDE_LIBRARIES asio;container;json;circular_buffer;beast;outcome;url;leaf)
add_subdirectory(boost EXCLUDE_FROM_ALL)

# Fix missing find package on threads
find_package(Threads)
set(BOOST_ASYNC_BUILD_EXAMPLES ON)
set(BOOST_ASYNC_BUILD_INLINE ON)
set(BOOST_ASYNC_BUILD_TESTS OFF)
add_subdirectory(async)
target_compile_options(boost_async PRIVATE -Wall -Wextra -Wno-unused-parameter)
# Fix missing libraries
target_link_libraries(boost_async PUBLIC Boost::asio Boost::container Boost::circular_buffer)
# Fix missing libs needed by examples
target_link_libraries(boost_async PUBLIC Boost::outcome Boost::beast Boost::url Boost::leaf)

# --------------------------------------------------
# My own stuff
# --------------------------------------------------

add_subdirectory(examples)

