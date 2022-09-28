#include <iostream>
#include <omp.h>
#include <vector>

int main() {
  int num_samples = 1000000;
  int num_inside = 0;
  // generate random points between 0 and 1
#pragma omp parallel for reduction(+ : num_inside)
  for (int i = 0; i < num_samples; i++) {
    int x = rand() / (float)RAND_MAX;
    int y = rand() / (float)RAND_MAX;
    if (x * x + y * y < 1) {
      num_inside++;
    }
  }
  std::cout << "Estimated pi: " << 4 * num_inside / (float)num_samples
            << std::endl;
  return 0;
}
