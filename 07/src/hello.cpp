#include <omp.h>
#include <iostream>

int main() {
#pragma omp parallel
  {
    int id = omp_get_thread_num();
    std::cout << "Hello Thread " << id << std::endl;
  }

  return 0;
}
