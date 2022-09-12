from multiprocessing import Process, Queue, shared_memory
import numpy as np

def create_array(size):
    tmp = np.random.randint(0, 100, size, dtype=np.int32)
    shm = shared_memory.SharedMemory(create=True, size=tmp.nbytes)
    array = np.ndarray(tmp.shape, dtype=tmp.dtype, buffer=shm.buf)
    array[:] = tmp[:]

    return shm, array

def add_one(shm, arr_len, idx):
    array = np.ndarray((arr_len,), dtype=np.int32, buffer=shm.buf)
    array[idx] += 1

if __name__=='__main__':
    DATA_SIZE = 10
    shm, data = create_array(DATA_SIZE)

    print(data)
    processes = []
    for i in range(len(data)):
        process = Process(target=add_one, args=(shm, DATA_SIZE, i))
        processes.append(process)

    for process in processes:
        process.start()

    for process in processes:
        process.join()

    print(data)

    del data
    shm.close()
    shm.unlink()
