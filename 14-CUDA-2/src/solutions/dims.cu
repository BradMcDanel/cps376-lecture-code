#include <stdio.h>

__global__ void print_id_1dgrid_1dblock() {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  printf("(%d) (%d) : %d\n", blockIdx.x, threadIdx.x, idx);
}

__global__ void print_id_1dgrid_2dblock() {
  // Use the 2D block and thread indices to calculate a unique 1D index
  // Then, print the 2D block and thread indices, and the 1D index

  // Hint: blockDim.x is the number of threads in a block in the x dimension
  //       blockDim.y is the number of threads in a block in the y dimension
  int idx = blockIdx.x * blockDim.x * blockDim.y + threadIdx.y * blockDim.x +
            threadIdx.x;
  printf("(%d, %d) (%d, %d) : %d\n", blockIdx.x, blockIdx.y, threadIdx.x,
         threadIdx.y, idx);
}

__global__ void print_id_1dgrid_3dblock() {
  // TODO: Implement this function
  // Hint: blockDim.z is the number of threads in a block in the z dimension
  int idx = blockIdx.x * blockDim.x * blockDim.y * blockDim.z +
            threadIdx.z * blockDim.y * blockDim.x + threadIdx.y * blockDim.x +
            threadIdx.x;
  printf("(%d, %d, %d) (%d, %d, %d) : %d\n", blockIdx.x, blockIdx.y, blockIdx.z,
         threadIdx.x, threadIdx.y, threadIdx.z, idx);
}

int main(void) {
  //    grid:  x, y, z
  dim3 dimGrid(2, 1, 1);

  //    block:  x, y, z
  dim3 dimBlock(4, 1, 1);

  printf("1D grid, 1D block:\n");
  print_id_1dgrid_1dblock<<<dimGrid, dimBlock>>>();
  cudaDeviceSynchronize(); // Do this between kernel launches to ensure that
                           // the previous kernel has finished executing

  // TODO: implement print_id_1dgrid_2dblock and print_id_1dgrid_3dblock
  dim3 dimGrid2(2, 1, 1);
  dim3 dimBlock2(2, 2, 1);
  printf("1D grid, 2D block:\n");
  print_id_1dgrid_2dblock<<<dimGrid2, dimBlock2>>>();
  cudaDeviceSynchronize();

  dim3 dimGrid3(2, 1, 1);
  dim3 dimBlock3(2, 2, 3);
  printf("1D grid, 3D block:\n");
  print_id_1dgrid_3dblock<<<dimGrid3, dimBlock3>>>();
  cudaDeviceSynchronize();

  return 0;
}
