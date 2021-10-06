#include <stdio.h>
#include <time.h>

__global__ void vector_add(int *a, int *b, int *c, int N) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < N) {
    c[idx] = a[idx] + b[idx];
  }
}

void cpu_vector_add(int *a, int *b, int *c, int N) {
  for (int i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <N>\n", argv[0]);
    return 1;
  }

  int N = atoi(argv[1]);
  int *a, *b, *c, *c_ref;
  int *d_a, *d_b, *d_c;
  int size = N * sizeof(int);

  // Set the CUDA device
  cudaSetDevice(0);

  // Allocate space for device copies of a, b, c
  cudaMalloc((void **)&d_a, size);
  cudaMalloc((void **)&d_b, size);
  cudaMalloc((void **)&d_c, size);

  // Setup input values
  a = (int *)malloc(size);
  b = (int *)malloc(size);
  c = (int *)malloc(size);
  c_ref = (int *)malloc(size);

  // fill a and b with random values
  for (int i = 0; i < N; i++) {
    a[i] = rand() % 10;
    b[i] = rand() % 10;
  }

  // Copy input from host to device
  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

  int block_size = 256;
  dim3 dimGrid(N / block_size, 1, 1);
  dim3 dimBlock(block_size, 1, 1);

  // start timer
  clock_t start = clock();

  // call the kernel
  vector_add<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, N);

  // stop timer
  clock_t end = clock();

  // copy result back to host
  cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

  double time_spent_gpu = (double)(end - start) / CLOCKS_PER_SEC;

  // call the CPU version
  clock_t start_cpu = clock();
  cpu_vector_add(a, b, c_ref, N);
  clock_t end_cpu = clock();
  double time_spent_cpu = (double)(end_cpu - start_cpu) / CLOCKS_PER_SEC;

  // compare results
  for (int i = 0; i < N; i++) {
    if (c[i] != c_ref[i]) {
      printf("Error: c[%d] = %d, c_ref[%d] = %d\n", i, c[i], i, c_ref[i]);
      return 1;
    }
  }

  printf("GPU time: %f\n", time_spent_gpu);
  printf("CPU time: %f\n", time_spent_cpu);

  // Cleanup
  free(a);
  free(b);
  free(c);
  free(c_ref);
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

  // Exit program
  return 0;
}
