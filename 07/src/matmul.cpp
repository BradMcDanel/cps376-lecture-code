#include <chrono>
#include <iostream>
#include <omp.h>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

class Matrix {
public:
  int *d;
  int rows;
  int cols;

  Matrix(int rows, int cols) : rows(rows), cols(cols) {
    d = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
      d[i] = 0;
    }
  }
};

// A perf comparison of serial matmul, serial tiled matmul, and
// parallel matmul using omp.
Matrix serial_matmul(const Matrix &A, const Matrix &B) {
  Matrix C(A.rows, B.cols);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.cols; j++) {
      for (int k = 0; k < A.cols; k++) {
        C.d[i * B.cols + j] += A.d[i * A.cols + k] * B.d[k * B.cols + j];
      }
    }
  }

  return C;
}

Matrix serial_tiled_matmul(const Matrix &A, const Matrix &B, int tile_size) {
  Matrix C(A.rows, B.cols);
  int tile_rows = A.rows / tile_size;
  int tile_cols = B.cols / tile_size;

  for (int i = 0; i < tile_rows; i++) {
    for (int j = 0; j < tile_cols; j++) {
      for (int k = 0; k < tile_size; k++) {
        for (int l = 0; l < tile_size; l++) {
          C.d[i * B.cols + j] += A.d[i * A.cols + k * tile_size + l] *
                                 B.d[l * B.cols + j * tile_size + k];
        }
      }
    }
  }

  return C;
}

bool equals(const Matrix &A, const Matrix &B) {
  for (int i = 0; i < A.rows * A.cols; i++) {
    if (A.d[i] == B.d[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int n = 1000;
  int tile_size = 1;
  Matrix A(n, n);
  Matrix B(n, n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A.d[i * n + j] = rand() % 2;
      B.d[i * n + j] = rand() % 2;
    }
  }

  // warmup
  Matrix C = serial_matmul(A, B);
  std::cout << C.d[0] << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  C = serial_matmul(A, B);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "serial matmul took " << micros(end - start).count() << " us"
            << std::endl;

  start = std::chrono::high_resolution_clock::now();
  Matrix D = serial_tiled_matmul(A, B, tile_size);
  end = std::chrono::high_resolution_clock::now();
  std::cout << "serial tiled matmul took " << micros(end - start).count()
            << " us" << std::endl;

  // start = std::chrono::high_resolution_clock::now();
  // Matrix E = parallel_matmul(A, B, tile_size);
  // end = std::chrono::high_resolution_clock::now();
  // std::cout << "serial tiled matmul took " << micros(end - start).count()
  //           << " us" << std::endl;

  // std::cout << "Results are the same? " << equals(C, D) << std::endl;
  // std::cout << "Results are the same? " << equals(C, E) << std::endl;

  return 0;
}