cmake_minimum_required(VERSION 3.1)
project(lecture-code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(race src/race.cpp)
target_include_directories(race PRIVATE include)
target_link_libraries(race PRIVATE Threads::Threads)

add_executable(mutex_example src/mutex_example.cpp)
target_include_directories(mutex_example PRIVATE include)
target_link_libraries(mutex_example PRIVATE Threads::Threads)

add_executable(mutex_impl src/mutex_impl.cpp)
target_include_directories(mutex_impl PRIVATE include)
target_link_libraries(mutex_impl PRIVATE Threads::Threads)

add_executable(deadlock src/deadlock.cpp)
target_include_directories(deadlock PRIVATE include)
target_link_libraries(deadlock PRIVATE Threads::Threads)

add_executable(sum_serial src/sum_serial.cpp)
target_include_directories(sum_serial PRIVATE include)
target_link_libraries(sum_serial PRIVATE Threads::Threads)

add_executable(sum_parallel src/sum_parallel.cpp)
target_include_directories(sum_parallel PRIVATE include)
target_link_libraries(sum_parallel PRIVATE Threads::Threads)

add_executable(sum_parallel_sol src/sum_parallel_sol.cpp)
target_include_directories(sum_parallel_sol PRIVATE include)
target_link_libraries(sum_parallel_sol PRIVATE Threads::Threads)
