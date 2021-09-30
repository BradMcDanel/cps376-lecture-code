#include <iostream>
#include <omp.h>
#include <vector>

#include "image.h"

double estimate_area(Image &img, int N, int M) {
  omp_set_num_threads(N);

  std::vector<int> sums;
  for (size_t i = 0; i < N; i++) {
    sums.push_back(0);
  }

#pragma omp parallel for
  for (size_t i = 0; i < N * M; i++) {
    int tid = omp_get_thread_num();
    int x = rand() % img.w;
    int y = rand() % img.h;
    if (img.get(x, y) != 255) {
      sums[tid]++;
    }
  }

  int final_sum = 0;
  for (size_t i = 0; i < N; i++) {
    final_sum += sums[i];
  }

  double area = final_sum / double(N * M);
  return area;
}

int main() {
  // Reads in a image (and converts to greyscale for simplicity)
  Image img("../data/fm.png");

  int N = 4;
  int M = 100;

  std::cout << estimate_area(img, N, 10) << std::endl;
  std::cout << estimate_area(img, N, 100) << std::endl;
  std::cout << estimate_area(img, N, 1000) << std::endl;
  std::cout << estimate_area(img, N, 10000) << std::endl;
  std::cout << estimate_area(img, N, 100000) << std::endl;

  return 0;
}
