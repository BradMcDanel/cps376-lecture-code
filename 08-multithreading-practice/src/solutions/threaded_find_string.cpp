#include <iostream>
#include <thread>
#include <vector>

#include "random_string.h"

#define STR_LENGTH 8388608
#define NUM_THREADS 4

void find_string(std::string &str, std::string &substr, size_t start_idx,
                 size_t end_idx, int &idx) {
  for (size_t i = start_idx; i < end_idx; i++) {
    for (size_t j = 0; j < substr.size(); j++) {
      if (str[i + j] != substr[j]) {
        break;
      }
      if (j == substr.size() - 1) {
        idx = i;
        return;
      }
    }
  }
}

int main() {
  std::string str = random_string(STR_LENGTH);
  std::string substr = "pizza";
  std::vector<std::thread> threads;
  std::vector<int> results(NUM_THREADS, -1);

  for (int i = 0; i < NUM_THREADS; i++) {
    // start and end must overlap by substr.size() - 1
    size_t start_idx = i * str.size() / NUM_THREADS;
    if (i > 0) {
      start_idx -= substr.size() - 1;
    }
    size_t end_idx = (i + 1) * str.size() / NUM_THREADS;
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
