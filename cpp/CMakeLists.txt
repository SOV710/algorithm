cmake_minimum_required(VERSION 3.28)
project(algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithm main.cpp)

add_subdirectory(lib)

target_link_libraries(algorithm PRIVATE
        algorithm_lib)
