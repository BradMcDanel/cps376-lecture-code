/*
 * Taken from here and modified:
 * https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array
 */

#include <algorithm>
#include <ctime>
#include <iostream>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

int main() {
  // Generate data
  const unsigned arraySize = 32768;
  const unsigned numSamples = 100000;
  int data[arraySize];

  for (unsigned c = 0; c < arraySize; c++) {
    data[c] = std::rand() % 256;
  }

  // Unsorted array benchmark
  auto start = std::chrono::high_resolution_clock::now();
  long long sum_unsorted = 0;
  for (unsigned i = 0; i < numSamples; i++) {
    for (unsigned c = 0; c < arraySize; c++) {
      if (data[c] >= 128) {
        sum_unsorted += data[c];
      }
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto unsorted_duration = micros(end - start).count();

  // With this, the next loop runs faster
  std::sort(data, data + arraySize);

  // Sorted array benchmark
  start = std::chrono::high_resolution_clock::now();
  long long sum_sorted = 0;
  for (unsigned i = 0; i < numSamples; i++) {
    for (unsigned c = 0; c < arraySize; c++) {
      if (data[c] >= 128) {
        sum_sorted += data[c];
      }
    }
  }
  end = std::chrono::high_resolution_clock::now();
  auto sorted_duration = micros(end - start).count();

  std::cout << "Unsorted Sum: " << sum_unsorted << std::endl;
  std::cout << "Sorted Sum: " << sum_sorted << std::endl;
  std::cout << "Unsorted Duration (high branch mispredict): "
            << unsorted_duration << std::endl;
  std::cout << "Sorted Duration (low branch mispredict): " << sorted_duration
            << std::endl;
}
