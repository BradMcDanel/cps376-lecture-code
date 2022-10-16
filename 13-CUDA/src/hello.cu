#include <stdio.h>

__global__ void print_id() {
  printf("(%d %d %d) (%d %d %d)\n", blockIdx.x, blockIdx.y, blockIdx.z,
         threadIdx.x, threadIdx.y, threadIdx.z);
}

int main(void) {
  int N = 1000000;
  int grid = N / 1024;
  // specify grid and block dimensions
  dim3 dimGrid(grid, 1, 1);
  dim3 dimBlock(1024, 1, 1);

  // launch kernel
  print_id<<<dimGrid, dimBlock>>>();

  // ensure the kernel is launched before program exits
  cudaDeviceSynchronize();

  return 0;
}
