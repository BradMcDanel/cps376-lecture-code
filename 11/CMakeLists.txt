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

add_executable(vector_add src/vector_add.cu)
target_include_directories(vector_add PRIVATE include)

add_executable(matmul src/matmul.cu)
target_include_directories(matmul PRIVATE include)
