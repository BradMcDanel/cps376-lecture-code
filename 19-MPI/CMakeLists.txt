cmake_minimum_required(VERSION 3.1)
project(lecture-code)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(hello_mpi src/hello_mpi.cpp)
target_link_libraries(hello_mpi ${MPI_LIBRARIES})

add_executable(send_recv src/send_recv.cpp)
target_link_libraries(send_recv ${MPI_LIBRARIES})

add_executable(chain src/chain.cpp)
target_link_libraries(chain ${MPI_LIBRARIES})

add_executable(sum_range src/sum_range.cpp)
target_link_libraries(sum_range ${MPI_LIBRARIES})
