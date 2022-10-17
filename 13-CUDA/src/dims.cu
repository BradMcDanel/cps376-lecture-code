#include <stdio.h>

__global__ void print_id() {
  printf("(%d %d %d) (%d %d %d)\n", blockIdx.x, blockIdx.y, blockIdx.z,
         threadIdx.x, threadIdx.y, threadIdx.z);
}

int main(void) {
  // Specify grid and block dimensions
  // These support 3D grids and blocks, but we'll only use 1D for now
  dim3 dimGrid(2, 4, 8);
  dim3 dimBlock(1, 2, 3);

  // launch kernel
  print_id<<<dimGrid, dimBlock>>>();

  // ensure the kernel is launched before program exits
  cudaDeviceSynchronize();

  return 0;
}
