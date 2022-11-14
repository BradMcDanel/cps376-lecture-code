#include <iostream>

#include "mpi.h"

int main(int argc, char *argv[]) {
  // Initialize MPI
  MPI::Init(argc, argv);

  // Get the number of processes
  int numP = MPI::COMM_WORLD.Get_size();

  // Get the ID of the process
  int myId = MPI::COMM_WORLD.Get_rank();

  // Compute left and reight neighbors
  int left = (myId == 0) ? numP - 1 : myId - 1;
  int right = (myId == numP - 1) ? 0 : myId + 1;
  int number;
  if (myId == 0) {
    number = 0;
    MPI::COMM_WORLD.Send(&number, 1, MPI::INT, right, 0);
  } else {
    MPI::COMM_WORLD.Recv(&number, 1, MPI::INT, left, 0);

    // See what number this process received
    std::cout << "Process " << myId << " of " << numP
              << ": received number = " << number << std::endl;
  }

  // Increment the number and send it to the right
  number++;
  if (myId < numP - 1) {
    MPI::COMM_WORLD.Send(&number, 1, MPI::INT, right, 0);
  }

  // Proc numP - 1 prints the final number
  if (myId == numP - 1) {
    std::cout << "Final result: " << number << std::endl;
  }

  // Terminate MPI
  MPI::Finalize();

  return 0;
}
