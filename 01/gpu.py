import torch
import time

if __name__=='__main__':
    n = 4096
    m = 4096
    A = torch.rand(n, m).cuda()
    B = torch.rand(m, n).cuda()
    start_time = time.time()
    C = A @ B
    end_time = time.time()
    total_time = end_time - start_time
    print(f"Took {total_time} seconds.")

