#include <iostream>
#include <sstream> // istringstream can be used to split string on " ", useful for parsing commands
#include <unordered_map> // our kv_store

#include "mpi.h"

#define BUF_SIZE 1024
char msg_buf[BUF_SIZE]; // Used for all communication of strings

void spoke_logic(int myId, int numP) {
  // Our Key-Value store
  std::unordered_map<std::string, std::string> kv_store;

  // Types of messages
  // 1. PUT <procId> <key> <value>
  // 2. GET <key>
  // 3. DEL <key>
  // 4. EXIT

  while (true) {
    // Receive message from hub
    MPI::COMM_WORLD.Bcast(msg_buf, BUF_SIZE, MPI::CHAR, 0);

    // Parse message and do the right thing!
    // Refer to slides for details
    // I suggest starting with EXIT
  }
}

void hub_logic(int myId, int numP) {
  std::string command;
  std::cout << "Enter a command: " << std::endl
            << " -PUT <procId> <key> <value>" << std::endl
            << " -GET <key>" << std::endl
            << " -DEL <key>" << std::endl
            << " -EXIT" << std::endl;
  while (true) {
    std::cout << ">> ";
    std::cin >> command;

    if (command == "EXIT") {
      // Logic for EXIT command
    } // else if ...

    // HINT: you can read multiple words cin like so
    // std::string key, value;
    // std::cin >> key >> value;
  }
}

int main(int argc, char *argv[]) {
  // Don't need to change anything in main!
  // Run using: mpirun -np 4 kv_store

  // Initialize MPI
  MPI::Init(argc, argv);

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

  if (isHub) {
    hub_logic(myId, numP);
  } else {
    spoke_logic(myId, numP);
  }

  MPI::Finalize();

  return 0;
}
