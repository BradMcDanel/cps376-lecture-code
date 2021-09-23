cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -march=native -pipe")


add_executable(hello src/hello.cpp)
target_include_directories(hello PRIVATE include)
target_link_libraries(hello PUBLIC OpenMP::OpenMP_CXX)

add_executable(reduction src/reduction.cpp)
target_include_directories(reduction PRIVATE include)
target_link_libraries(reduction PUBLIC OpenMP::OpenMP_CXX)

# add_executable(matmul src/matmul.cpp)
# target_include_directories(matmul PRIVATE include)
# target_link_libraries(matmul PUBLIC OpenMP::OpenMP_CXX)
