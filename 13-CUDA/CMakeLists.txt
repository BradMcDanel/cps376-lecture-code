cmake_minimum_required(VERSION 3.1)
project(lecture-code LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -Wno-missing-field-initializers")

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 11)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

add_executable(hello src/hello.cu)
target_include_directories(hello PRIVATE include)

add_executable(allocation src/allocation.cu)
target_include_directories(allocation PRIVATE include)

add_executable(elementwise_add src/elementwise_add.cu)
target_include_directories(elementwise_add PRIVATE include)

add_executable(elementwise_add_sol src/solutions/elementwise_add.cu)
target_include_directories(elementwise_add_sol PRIVATE include)

add_executable(substring_finder src/substring_finder.cu)
target_include_directories(substring_finder PRIVATE include)

add_executable(substring_finder_sol src/solutions/substring_finder.cu)
target_include_directories(substring_finder_sol PRIVATE include)
