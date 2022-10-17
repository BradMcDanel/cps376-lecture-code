#include <stdio.h>
#include <stdlib.h>

__global__ void add(int *a, int *b, int *c, int n) {
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  if (index < n) {
    c[index] = a[index] + b[index];
  }
}

int main() {
  int n = 50;
  int *a = (int *)malloc(n * sizeof(int));
  int *b = (int *)malloc(n * sizeof(int));
  int *c = (int *)malloc(n * sizeof(int));

  // initialize `a`, `b`, and `c` with some values
  for (int i = 0; i < n; i++) {
    a[i] = i;
    b[i] = n - i;
  }

  // (1) allocate device memory for `a`, `b`, and `c`
  int *d_a, *d_b, *d_c;
  cudaMalloc(&d_a, n * sizeof(int));
  cudaMalloc(&d_b, n * sizeof(int));
  cudaMalloc(&d_c, n * sizeof(int));

  // (2) copy `a` and `b` to the device
  cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

  // (3) launch the kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
  add<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

  // (4) copy `c` back to the host
  cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

  // (5) print the result
  for (int i = 0; i < n; i++) {
    printf("%d + %d = %d\n", a[i], b[i], c[i]);
  }

  // (6) free device memory
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

  // (7) free host memory
  free(a);
  free(b);
  free(c);

  return 0;
}
