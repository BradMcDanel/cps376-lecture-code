cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(OpenMP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -Wno-missing-field-initializers")

add_executable(mnist_test src/mnist_test.cpp src/mnist.cpp)
target_include_directories(mnist_test PRIVATE include)

add_executable(knn_serial src/knn_serial.cpp src/mnist.cpp)
target_include_directories(knn_serial PRIVATE include)
target_link_libraries(knn_serial PUBLIC OpenMP::OpenMP_CXX)

add_executable(knn_parallel src/knn_parallel.cpp src/mnist.cpp)
target_include_directories(knn_parallel PRIVATE include)
target_link_libraries(knn_parallel PUBLIC OpenMP::OpenMP_CXX)
