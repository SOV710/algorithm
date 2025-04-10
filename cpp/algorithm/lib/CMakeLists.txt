#lib/CMakeLists.txt

add_library(algorithm_lib STATIC
        src/util.cpp
        src/sort.cpp
        src/tree.cpp)

target_include_directories(algorithm_lib PUBLIC
        include)