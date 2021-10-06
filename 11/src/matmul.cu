#include <stdio.h>

__global__ void matmul(float *a, float *b, float *c, int m, int n, int k) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;

  // this could be much more efficient!
  if (i < m && j < n) {
    float sum = 0;
    for (int p = 0; p < k; p++) {
      sum += a[i * k + p] * b[p * n + j];
    }
    c[i * n + j] = sum;
  }
}

int main(void) {
  int m = 1024;
  int n = 1024;
  int k = 1024;

  float *a, *b, *c;
  float *d_a, *d_b, *d_c;

  // allocate host memory
  a = (float *)malloc(m * k * sizeof(float));
  b = (float *)malloc(k * n * sizeof(float));
  c = (float *)malloc(m * n * sizeof(float));

  // allocate device memory
  cudaMalloc((void **)&d_a, m * k * sizeof(float));
  cudaMalloc((void **)&d_b, k * n * sizeof(float));
  cudaMalloc((void **)&d_c, m * n * sizeof(float));

  // initialize the matrices on the host
  for (int i = 0; i < m * k; i++) {
    a[i] = 1.0f;
  }

  for (int i = 0; i < k * n; i++) {
    b[i] = 1.0f;
  }

  // copy to device
  cudaMemcpy(d_a, a, m * k * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, k * n * sizeof(float), cudaMemcpyHostToDevice);

  dim3 dimGrid(m / 32, n / 32, 1);
  dim3 dimBlock(32, 32, 1);

  matmul<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, m, n, k);

  // copy back to host
  cudaMemcpy(c, d_c, m * n * sizeof(float), cudaMemcpyDeviceToHost);

  // verify the result
  for (int i = 0; i < m * n; i++) {
    if ((c[i] - k) > 1e-8) { // since all elements are 1.0f, this should be true
      printf("error: c[%d] = %f\n", i, c[i]);
      return -1;
    }
  }

  return 0;
}
