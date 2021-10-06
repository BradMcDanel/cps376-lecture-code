#include <stdio.h>

__global__ void print_id() {
  printf("(%d %d %d) (%d %d %d)\n", blockIdx.x, blockIdx.y, blockIdx.z,
         threadIdx.x, threadIdx.y, threadIdx.z);
}

int main(void) {
  // specify grid and block dimensions
  dim3 dimGrid(2, 2, 2);
  dim3 dimBlock(2, 2, 2);

  // launch kernel
  print_id<<<dimGrid, dimBlock>>>();

  // ensure the kernel is launched before program exits
  cudaDeviceSynchronize();

  return 0;
}
