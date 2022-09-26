cmake_minimum_required(VERSION 3.1)
project(lecture-code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra")

add_executable(queue_example src/queue_example.cpp)
target_include_directories(queue_example PRIVATE include)

add_executable(find_string src/find_string.cpp)
target_include_directories(find_string PRIVATE include)

add_executable(threaded_find_string src/threaded_find_string.cpp)
target_include_directories(threaded_find_string PRIVATE include)

add_executable(dining src/dining.cpp)
target_include_directories(dining PRIVATE include)

