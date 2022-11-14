#include <iostream>

#include "mpi.h"

int main(int argc, char *argv[]) {
  // Initialize MPI
  MPI::Init(argc, argv);

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <minval> <maxval>" << std::endl;
    MPI::Finalize();
    return 1;
  }

  int min_value = atoi(argv[1]);
  int max_value = atoi(argv[2]);
  int numP = MPI::COMM_WORLD.Get_size();
  int myId = MPI::COMM_WORLD.Get_rank();

  std::cout << min_value << " " << max_value << " " << numP << " " << myId
            << std::endl;

  // TODO: Compute the sum from min_value to max_value by splitting
  //       the range into numP parts (each part does ~equal work)
  //        - Only the process with ID 0 should print the final result
  //        - Feel free to organize the program however you like

  // Terminate MPI
  MPI::Finalize();

  return 0;
}
