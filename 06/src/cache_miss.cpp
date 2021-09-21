#include <iostream>
#include <vector>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

int main() {
  std::vector<int> v(1024 * 1024);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = rand() % 100;
  }

  // Sum the vector with linear access pattern
  auto start = std::chrono::high_resolution_clock::now();
  int sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum += v[i];
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Linear Access Time: " << micros(end - start).count() << " us"
            << std::endl;

  // Compute random permutation of vector indices
  std::vector<size_t> indices(v.size());
  for (size_t i = 0; i < indices.size(); i++) {
    indices[i] = i;
  }
  std::random_shuffle(indices.begin(), indices.end());

  // Sum the vector with random access pattern
  sum = 0;
  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < indices.size(); i++) {
    sum += v[indices[i]];
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Random Access Time: " << micros(end - start).count() << " us"
            << std::endl;

  return 0;
}