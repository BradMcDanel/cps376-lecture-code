#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void sum_func(int start_idx, int end_idx, std::vector<int>& arr, int& sum) {
  for (int i = start_idx; i < end_idx; i++) {
    sum += arr[i];
  }
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
    int start_idx = i * arr.size() / 4;
    int end_idx = (i + 1) * arr.size() / 4;
    std::thread t(sum_func, start_idx, end_idx, std::ref(arr),
                  std::ref(sums[i]));
    threads.push_back(std::move(t));
  }

  for (auto& t : threads) {
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