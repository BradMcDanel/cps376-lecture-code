#include <iostream>
#include <omp.h>

int main() {
  // omp_set_num_threads(2);
#pragma omp parallel ordered
  {
    int id = omp_get_thread_num();
    std::cout << "Hello Thread " << id << std::endl;
  }

  return 0;
}
