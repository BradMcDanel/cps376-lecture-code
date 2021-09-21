cmake_minimum_required(VERSION 3.1)
project(lecture-code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -march=native -pipe")


add_executable(cache_miss src/cache_miss.cpp)
target_include_directories(cache_miss PRIVATE include)

add_executable(iter_comp src/iter_comp.cpp)
target_include_directories(iter_comp PRIVATE include)

add_executable(alloc_comp src/alloc_comp.cpp)
target_include_directories(alloc_comp PRIVATE include)

