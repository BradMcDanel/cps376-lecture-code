import time
import random

"""
Naive matrix mutliplication.
"""
def matmul(A, B):
    """
    Matrix multiplication.
    """
    C = [[0 for i in range(len(A[0]))] for j in range(len(A))]
    for i in range(len(A)):
        for j in range(len(A[0])):
            for k in range(len(A[0])):
                C[i][j] += A[i][k] * B[k][j]
    return C

def build_mat(n, m):
    """
    Build a n x m matrix.
    """
    A = [[0. for i in range(m)] for j in range(n)]
    for i in range(n):
        for j in range(m):
            A[i][j] = random.random()
    return A

if __name__ == "__main__":
    n = 512
    m = 512
    A = build_mat(n, m)
    B = build_mat(m, n)
    start_time = time.time()
    C = matmul(A, B)
    end_time = time.time()
    total_time = end_time - start_time

    print(f"Took {total_time} seconds.")
