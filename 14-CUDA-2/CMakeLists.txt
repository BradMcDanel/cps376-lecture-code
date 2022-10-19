cmake_minimum_required(VERSION 3.1)
project(lecture-code LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -Wno-missing-field-initializers")

if(NOT DEFINED CMAKE_CUDA_STANDARD)
    set(CMAKE_CUDA_STANDARD 11)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

add_executable(dims src/dims.cu)
target_include_directories(dims PRIVATE include)

add_executable(dims_sol src/solutions/dims.cu)
target_include_directories(dims_sol PRIVATE include)

add_executable(matmul src/matmul.cu)
target_include_directories(matmul PRIVATE include)

add_executable(tiled_matmul src/tiled_matmul.cu)
target_include_directories(tiled_matmul PRIVATE include)
