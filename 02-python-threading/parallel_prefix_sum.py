"""
Parallel prefix sum (e.g., cumulative sum) using python mutliprocessing
"""
import time
import sys
from multiprocessing import Process, Queue, shared_memory
import numpy as np

def create_random_array(size):
    tmp = np.random.randint(0, 5, size, dtype=np.int32)
    shm = shared_memory.SharedMemory(create=True, size=tmp.nbytes)
    array = np.ndarray(tmp.shape, dtype=tmp.dtype, buffer=shm.buf)
    array[:] = tmp[:]

    return shm, array

def create_zeros_array(size):
    tmp = np.zeros(size, dtype=np.int32)
    shm = shared_memory.SharedMemory(create=True, size=tmp.nbytes)
    array = np.ndarray(tmp.shape, dtype=tmp.dtype, buffer=shm.buf)
    array[:] = tmp[:]

    return shm, array


def parallel_prefix_sum(input_shm, output_shm, proc_shm, arr_len, pid, num_processes):
    input_data = np.ndarray((arr_len,), dtype=np.int32, buffer=input_shm.buf)
    output_data = np.ndarray((arr_len,), dtype=np.int32, buffer=output_shm.buf)
    proc_buf = np.ndarray((num_processes,), dtype=np.int32, buffer=proc_shm.buf)

    # calculate the start and end indices for each process
    start = pid * (arr_len // num_processes)
    end = (pid + 1) * (arr_len // num_processes)

    # calculate the prefix sum for each process
    curr_sum = 0
    for i in range(start, end):
        curr_sum += input_data[i]
        output_data[i] = curr_sum

    # store the last element of each process in the proc_buf
    proc_buf[pid] = output_data[end - 1]

    # pid 0 does not need to wait for any other processes
    if pid == 0:
        return

    # wait until proc_buf is filled
    all_full = False
    while not all_full:
        all_full = True
        for i in range(num_processes):
            if proc_buf[i] == 0:
                all_full = False
                break
    
    # sum the proc_buf of 0..pid-1
    prev_sum = 0
    for i in range(pid):
        prev_sum += proc_buf[i]

    # add the sum to the output_data
    for i in range(start, end):
        output_data[i] += prev_sum


if __name__=='__main__':
    num_procs = int(sys.argv[1])
    DATA_SIZE = 2**24
    input_shm, input_data = create_random_array(DATA_SIZE)
    output_shm, output_data = create_zeros_array(DATA_SIZE)
    proc_shm, proc_buf = create_zeros_array(num_procs)

    # print(input_data)
    processes = []
    for pid in range(num_procs):
        process = Process(
            target=parallel_prefix_sum,
            args=(input_shm, output_shm, proc_shm, DATA_SIZE, pid, num_procs)
        )
        processes.append(process)

    start = time.time()
    for process in processes:
        process.start()

    for process in processes:
        process.join()
    
    end = time.time()
    total_time = end - start

    print("Is our solution correct? ", np.allclose(np.cumsum(input_data), output_data))
    print("Total time: ", total_time)

    input_shm.close()
    input_shm.unlink()
    output_shm.close()
    output_shm.unlink()
    proc_shm.close()
    proc_shm.unlink()
