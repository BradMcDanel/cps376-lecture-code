cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(OpenMP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -Wno-missing-field-initializers")

add_executable(hello_openmp src/hello_openmp.cpp)
target_include_directories(hello_openmp PRIVATE include)
target_link_libraries(hello_openmp PUBLIC OpenMP::OpenMP_CXX)

add_executable(critical_openmp src/critical_openmp.cpp)
target_include_directories(critical_openmp PRIVATE include)
target_link_libraries(critical_openmp PUBLIC OpenMP::OpenMP_CXX)

add_executable(sum_threads src/sum_threads.cpp)
target_include_directories(sum_threads PRIVATE include)

add_executable(sum_openmp src/sum_openmp.cpp)
target_include_directories(sum_openmp PRIVATE include)
target_link_libraries(sum_openmp PUBLIC OpenMP::OpenMP_CXX)

add_executable(monte_carlo src/monte_carlo.cpp)
target_include_directories(monte_carlo PRIVATE include)
target_link_libraries(monte_carlo PUBLIC OpenMP::OpenMP_CXX)

add_executable(downsample src/downsample.cpp)
target_include_directories(downsample PRIVATE include)
target_link_libraries(downsample PUBLIC OpenMP::OpenMP_CXX)

