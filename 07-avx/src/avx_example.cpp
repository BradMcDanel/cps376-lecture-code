#include <chrono>
#include <immintrin.h>
#include <iostream>

int main() {
  // create two vectors of 8 floats
  __m256 a = _mm256_setr_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
  __m256 b = _mm256_setr_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

  // add the two vectors
  __m256 c = _mm256_add_ps(a, b);

  // multiply the two vectors
  __m256 d = _mm256_mul_ps(a, b);

  // print the result
  float *c_ptr = (float *)&c;

  for (int i = 0; i < 8; i++) {
    std::cout << c_ptr[i] << std::endl;
  }

  std::cout << std::endl;

  for (int i = 0; i < 8; i++) {
    std::cout << d[i] << std::endl;
  }

  return 0;
}