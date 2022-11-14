#include "stdio.h"
#include "time.h"

#define TILE_SIZE 16

void cpu_matmul(float *a, float *b, float *c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      float sum = 0;
      for (int k = 0; k < n; k++) {
        sum += a[i * n + k] * b[k * n + j];
      }
      c[i * n + j] = sum;
    }
  }
}

__global__ void matmul(float *a, float *b, float *c, int n) {
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  // TODO: implement matrix multiplication
  // We assume matricies are square
  float sum = 0;
  for (int k = 0; k < n; k++) {
    sum += a[row * n + k] * b[k * n + col];
  }
  c[row * n + col] = sum;
}

int main(int argc, char **argv) {
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    printf("Usage: %s <matrix size>\n", argv[0]);
    return 0;
  }

  int size = n * n * sizeof(float);
  float *a, *b, *c, *c_gpu;
  float *d_a, *d_b, *d_c;
  a = (float *)malloc(size);
  b = (float *)malloc(size);
  c = (float *)malloc(size);
  c_gpu = (float *)malloc(size);
  cudaMalloc(&d_a, size);
  cudaMalloc(&d_b, size);
  cudaMalloc(&d_c, size);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i * n + j] = 1.0;
      b[i * n + j] = 1.0;
    }
  }
  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

  // CPU matmul
  clock_t start = clock();
  cpu_matmul(a, b, c, n);
  clock_t end = clock();
  double time_spent = (1000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("CPU matmul time: %f ms\n", time_spent);

  // Simple GPU matmul
  dim3 dimBlock(TILE_SIZE, TILE_SIZE);
  dim3 dimGrid(n / dimBlock.x, n / dimBlock.y);
  start = clock();
  matmul<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, n);
  cudaDeviceSynchronize();
  end = clock();
  time_spent = (1000 * (double)(end - start) / CLOCKS_PER_SEC);
  printf("Time for gpu matrix multiplication: %f ms\n", time_spent);
  cudaMemcpy(c_gpu, d_c, size, cudaMemcpyDeviceToHost);

  // Check results
  for (int i = 0; i < n * n; i++) {
    if (c[i] != c_gpu[i]) {
      printf("Error: c[%d] = %f, c_gpu[%d] = %f\n", i, c[i], i, c_gpu[i]);
      break;
    }
  }

  // Cleanup
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  free(a);
  free(b);
  free(c);
  free(c_gpu);

  return 0;
}