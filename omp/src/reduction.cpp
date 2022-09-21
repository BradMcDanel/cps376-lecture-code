#include <omp.h>
#include <chrono>
#include <iostream>
#include <vector>

// Just to make it easier to read...
template <typename T>
std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

void serial_reduce(std::vector<int>& v) {
  auto start = std::chrono::high_resolution_clock::now();
  auto sum = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    sum += v[i];
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "=====SERIAL REDUCE=====" << std::endl;
  std::cout << "sum " << sum << std::endl;
  std::cout << "serial time " << micros(end - start).count() << " us"
            << std::endl
            << std::endl;
}

void buggy_omp_reduce(std::vector<int>& v) {
  auto start = std::chrono::high_resolution_clock::now();
  auto sum = 0;
#pragma omp parallel for
  for (size_t i = 0; i < v.size(); ++i) {
    sum += v[i];
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "=====BUGGY OMP REDUCE=====" << std::endl;
  std::cout << "sum " << sum << std::endl;
  std::cout << "omp time " << micros(end - start).count() << " us" << std::endl
            << std::endl;
}

void omp_reduce(std::vector<int>& v) {
  auto start = std::chrono::high_resolution_clock::now();
  auto sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (size_t i = 0; i < v.size(); ++i) {
    sum += v[i];
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "=====OMP REDUCE=====" << std::endl;
  std::cout << "sum " << sum << std::endl;
  std::cout << "omp time " << micros(end - start).count() << " us" << std::endl
            << std::endl;
}

int main() {
  std::vector<int> v(1024 * 1024 * 16);
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] = rand() % 100;
  }

  serial_reduce(v);
  buggy_omp_reduce(v);
  omp_reduce(v);

  return 0;
}