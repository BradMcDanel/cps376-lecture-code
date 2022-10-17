#include <stdio.h>

__global__ void hello_cuda() {
  int thread_id = blockIdx.x * blockDim.x + threadIdx.x;
  printf("Hello from %d\n", thread_id);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number of threads>\n", argv[0]);
    return 1;
  }

  int num_threads = atoi(argv[1]);

  hello_cuda<<<1, num_threads>>>();

  // ensure the kernel is launched before program exits
  cudaDeviceSynchronize();

  return 0;
}
