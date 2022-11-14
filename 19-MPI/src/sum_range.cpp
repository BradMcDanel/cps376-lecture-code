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

  // TODO: Compute the sum from min_value to max_value by splitting
  //       the range into numP parts (each part does ~equal work)
  //        - Only the process with ID 0 should print the final result
  //        - Feel free to organize the program however you like
  int value_range = max_value - min_value;
  int start_val = value_range * (myId / float(numP));
  int end_val = value_range * ((myId + 1) / float(numP));

  int local_sum = 0;
  for (int i = start_val; i < end_val; i++) {
    local_sum += i;
  }

  std::cout << start_val << " " << end_val << " " << local_sum << " " << numP
            << " " << myId << std::endl;

  if (myId > 0) {
    MPI::COMM_WORLD.Send(&local_sum, 1, MPI::INT, 0, 0);
  } else {
    int other_sum;
    for (int id = 1; id < numP; id++) {
      MPI::COMM_WORLD.Recv(&other_sum, 1, MPI::INT, id, 0);
      local_sum += other_sum;
    }

    std::cout << "final sum " << local_sum << std::endl;
  }

  // Terminate MPI
  MPI::Finalize();

  return 0;
}
