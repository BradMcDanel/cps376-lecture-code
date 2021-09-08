#include <immintrin.h>
#include <chrono>
#include <iostream>
#include <vector>

// Just to make it easier to read...
template <typename T>
std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

float sum(const std::vector<float>& v) {
  float sum = 0;
  for (auto& x : v) {
    sum += x;
  }
  return sum;
}

float sum_avx_256(const std::vector<float>& v) {
  __m256 sum = _mm256_setzero_ps();
  for (size_t i = 0; i < v.size(); i += 8) {
    __m256 x = _mm256_load_ps(&v[i]);
    sum = _mm256_add_ps(sum, x);
  }

  float result[8];
  _mm256_store_ps(result, sum);
  float final_sum = 0;
  for (auto& x : result) {
    final_sum += x;
  }
  return final_sum;
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
  std::cout << "sum time: " << micros(end - start).count() << " us"
            << std::endl;
  std::cout << "sum_avx time: " << micros(end - start).count() << " us"
            << std::endl;
  std::cout << "speedup: " << serial_duration / avx_duration << "x"
            << std::endl;

  return 0;
}