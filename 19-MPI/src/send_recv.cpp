#include <iostream>

#include "mpi.h"

int main(int argc, char *argv[]) {
  // Initialize MPI
  MPI::Init(argc, argv);
  int numP = MPI::COMM_WORLD.Get_size();
  int myId = MPI::COMM_WORLD.Get_rank();
  if (numP != 2) {
    std::cerr << "This program requires two processes." << std::endl;
    MPI::Finalize();
    return 1;
  }

  // Proc 0 sends to Proc 1
  if (myId == 0) {
    int number = 7;
    MPI::COMM_WORLD.Send(&number, 1, MPI::INT, 1, 0);
    std::cout << "Process " << myId << " of " << numP
              << ": sent number = " << number << std::endl;
  }
  // Proc 1 receives from Proc 0
  else if (myId == 1) {
    int number;
    MPI::COMM_WORLD.Recv(&number, 1, MPI::INT, 0, 0);
    std::cout << "Process " << myId << " of " << numP
              << ": received number = " << number << std::endl;
  }

  // Terminate MPI
  MPI::Finalize();

  return 0;
}
