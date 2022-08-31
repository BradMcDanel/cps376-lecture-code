#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 Naive matrix mutliplication.
*/
void naive_matrix_multiply(int n, int m, int p, int *A, int *B, int *C) {
  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      C[i * p + j] = 0;
      for (k = 0; k < m; k++) {
        C[i * p + j] += A[i * m + k] * B[k * p + j];
      }
    }
  }
}

void init_matrix(int n, int m, int *A) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      A[i * m + j] = rand() % 10;
    }
  }
}

int main(void) {
  srand(time(NULL));
  int n = 2048;
  int m = 2048;
  int p = 2048;
  int *A = (int *)malloc(n * m * sizeof(int));
  int *B = (int *)malloc(m * p * sizeof(int));
  int *C = (int *)malloc(n * p * sizeof(int));
  init_matrix(n, m, A);
  init_matrix(m, p, B);
  clock_t start = clock();
  naive_matrix_multiply(n, m, p, A, B, C);
  clock_t end = clock();
  printf("Took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
  free(A);
  free(B);
  free(C);

  return 0;
}
