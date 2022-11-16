#include <iostream>
#include <string.h>

#include "mpi.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  // Initialize MPI
  MPI::Init(argc, argv);

  // Used for all communication of strings
  char msg_buf[BUF_SIZE];

  // Get the number of processes
  int numP = MPI::COMM_WORLD.Get_size();

  // Get the ID of the process
  int myId = MPI::COMM_WORLD.Get_rank();

  bool isHub;
  if (myId == 0) {
    isHub = true;
  } else {
    isHub = false;
  }

  // Broadcast from hub to all other processes
  if (isHub) {
    strncpy(msg_buf, "Hello World!", BUF_SIZE);
  }

  // Broadcast from hub to all other processes (it is a single call)
  MPI::COMM_WORLD.Bcast(msg_buf, BUF_SIZE, MPI::CHAR, 0);

  if (!isHub) {
    std::cout << "Process " << myId << " received: " << msg_buf << std::endl;
  }

  MPI::Finalize();

  return 0;
}
