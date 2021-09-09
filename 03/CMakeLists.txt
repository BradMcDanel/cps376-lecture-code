cmake_minimum_required(VERSION 3.1)
project(lecture-code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -march=native -pipe")


add_executable(avx src/avx.cpp)
target_include_directories(avx PRIVATE include)

add_executable(branching src/branching.cpp)
target_include_directories(branching PRIVATE include)
