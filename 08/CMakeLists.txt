cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(OpenMP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra -Wno-missing-field-initializers")

add_executable(mc_area src/mc_area.cpp)
target_include_directories(mc_area PRIVATE include)
target_link_libraries(mc_area PUBLIC OpenMP::OpenMP_CXX)

add_executable(downsample src/downsample.cpp)
target_include_directories(downsample PRIVATE include)
target_link_libraries(downsample PUBLIC OpenMP::OpenMP_CXX)

add_executable(upsample src/upsample.cpp)
target_include_directories(upsample PRIVATE include)
target_link_libraries(upsample PUBLIC OpenMP::OpenMP_CXX)

add_executable(string_search src/string_search.cpp)
target_include_directories(string_search PRIVATE include)
target_link_libraries(string_search PUBLIC OpenMP::OpenMP_CXX)
