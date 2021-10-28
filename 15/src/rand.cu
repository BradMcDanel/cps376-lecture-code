#include <stdio.h>
#include <stdlib.h>
#include <curand.h>
#include <curand_kernel.h>

__global__ void init_rand_kernel(curandState *state) {
 int idx = blockIdx.x * blockDim.x + threadIdx.x;
 curand_init(0, idx, 0, &state[idx]);
}

__global__ void use_rand_kernel(curandState *state) {
 int idx = blockIdx.x * blockDim.x + threadIdx.x;
 float rnd = curand_uniform(&state[idx]);
 printf("(%d), %f\n", idx, rnd);
}

curandState* init_rand(int n_threads, int n_blocks) {
  curandState *d_state;
  cudaMalloc(&d_state, n_threads * n_blocks * sizeof(curandState));
  init_rand_kernel<<<n_blocks, n_threads>>>(d_state);
  return d_state;
}

int main(void) {
  int n_threads = 16;
  int n_blocks = 1;
  curandState* d_state = init_rand(n_threads, n_blocks);
  use_rand_kernel<<<n_blocks, n_threads>>>(d_state);
  cudaDeviceSynchronize();

  return 0;
}
