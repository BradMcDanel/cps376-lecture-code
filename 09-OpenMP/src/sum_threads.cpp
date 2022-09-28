#include <iostream>
#include <thread>
#include <vector>

#define NUM_THREADS 2
int main() {
  std::vector<float> data = {1, 2, 3, 4, 5, 6, 7, 8};
  float sum = 0;
  std::vector<std::thread> threads;

  for (int i = 0; i < NUM_THREADS; i++) {
    // Fork
    threads.push_back(std::thread([&data, &sum, i]() {
      // Compute
      int start = i * data.size() / NUM_THREADS;
      int end = (i + 1) * data.size() / NUM_THREADS;
      for (int j = start; j < end; j++) {
        sum += data[j];
      }
    }));
  }
  // Join
  for (auto &t : threads) {
    t.join();
  }

  std::cout << sum << std::endl;
  return 0;
}
