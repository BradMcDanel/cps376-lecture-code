#include <iostream>
#include <thread>
#include <vector>

#include "random_string.h"

#define STR_LENGTH 8388608
#define NUM_THREADS 4

void find_string(std::string &str, std::string &substr, size_t start_idx,
                 size_t end_idx, int &idx) {
  // TODO: Implement find_string
}

int main() {
  std::string str = random_string(STR_LENGTH);
  std::string substr = "pizza";
  std::vector<std::thread> threads;

  // This vector will store the results of each thread
  // It is initialized to -1 so that we can check if a thread found the string
  std::vector<int> results(NUM_THREADS, -1);

  for (int i = 0; i < NUM_THREADS; i++) {
    // What should the start and end indices be?
    size_t start_idx = 0;
    size_t end_idx = 0;
    std::thread t(find_string, std::ref(str), std::ref(substr), start_idx,
                  end_idx, std::ref(results[i]));
    threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    if (results[i] != -1) {
      std::cout << "Found " << substr << " at index " << results[i]
                << std::endl;
      return 0;
    }
  }

  std::cout << "Found " << substr << " at index -1" << std::endl;
  return 0;
}
