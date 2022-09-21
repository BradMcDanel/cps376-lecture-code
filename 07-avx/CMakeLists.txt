cmake_minimum_required(VERSION 3.1)
project(lecture-code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -march=native -pipe")

add_executable(avx_example src/avx_example.cpp)
target_include_directories(avx_example PRIVATE include)

add_executable(sum_avx src/sum_avx.cpp)
target_include_directories(sum_avx PRIVATE include)

add_executable(sum_avx_sol src/sum_avx_sol.cpp)
target_include_directories(sum_avx_sol PRIVATE include)
