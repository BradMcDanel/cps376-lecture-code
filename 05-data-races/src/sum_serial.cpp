#include <chrono>
#include <iostream>
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

  int sum = 0;
  auto start = std::chrono::high_resolution_clock::now();
  sum_func(0, arr.size(), arr, sum);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sum: " << sum << " in " << duration.count() << " microseconds"
            << std::endl;

  return 0;
}