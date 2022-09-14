#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void sum_func(int start_idx, int end_idx, const std::vector<int> &arr,
              int &sum) {
  // TODO: Implement!
}

int main() {
  std::vector<int> arr(100000000);

  // initialize arr
  for (size_t i = 0; i < arr.size(); i++) {
    arr[i] = 1;
  }

  auto start = std::chrono::high_resolution_clock::now();
  // Divide the array into 4 threads
  std::vector<int> sums = {0, 0, 0, 0};
  std::vector<std::thread> threads;
  for (int i = 0; i < 4; i++) {

    // TODO: create a thread `t` and add to vector
    //       need to compute the start and end indexes

    // This should  be the last line of the for loop
    // threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  // Reduce the 4 sums to a single sum
  int sum = 0;
  for (int i = 0; i < 4; i++) {
    sum += sums[i];
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Sum: " << sum << " in " << duration.count() << " microseconds"
            << std::endl;

  return 0;
}