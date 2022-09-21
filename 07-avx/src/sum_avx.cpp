#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <vector>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

float sum(const std::vector<float> &v) {
  float sum = 0;
  for (auto &x : v) {
    sum += x;
  }
  return sum;
}

float sum_avx_256(const std::vector<float> &v) {
  // TODO: implement!
  return 0;
}

int main() {
  std::vector<float> v(8 * 1024 * 1024);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = 1;
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "sum: " << sum(v) << std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  float serial_duration = micros(end - start).count();

  start = std::chrono::high_resolution_clock::now();
  std::cout << "sum_avx: " << sum_avx_256(v) << std::endl;
  end = std::chrono::high_resolution_clock::now();
  float avx_duration = micros(end - start).count();

  // In real benchmarching code, we would want run this many iterations but
  // for simplicity, we just run it once.
  std::cout << "sum time: " << serial_duration << " us" << std::endl;
  std::cout << "sum_avx time: " << avx_duration << " us" << std::endl;
  std::cout << "speedup: " << serial_duration / avx_duration << "x"
            << std::endl;

  return 0;
}