cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(bcast src/kv_store.cpp)
target_link_libraries(bcast ${MPI_LIBRARIES})

add_executable(kv_store src/kv_store.cpp)
target_link_libraries(kv_store ${MPI_LIBRARIES})

# add_executable(kv_store_sol src/solutions/kv_store.cpp)
# target_link_libraries(kv_store_sol ${MPI_LIBRARIES})

