import time

from threading import Thread
from multiprocessing import Process

def hello(idx):
    print(f"Hello from {idx}!")

if __name__ == "__main__":
    N = 100
    # threads share the same memory space and have faster startup time
    # by default in python, threads run on a single core
    thread_start_time = time.time()
    threads = []
    for i in range(N):
        thread = Thread(target=hello, args=(i,))
        thread.start()
        threads.append(thread)
    
    for thread in threads:
        thread.join()
    thread_end_time = time.time()
    thread_total_time = thread_end_time - thread_start_time

    # processes have their own memory space and have slower startup time
    # processes run on multiple cores (in general)
    process_start_time = time.time()
    processes = []
    for i in range(N):
        process = Process(target=hello, args=(i,))
        process.start()
        processes.append(process)
        
    for process in processes:
        process.join()
    process_end_time = time.time()
    process_total_time = process_end_time - process_start_time

    print(f"Thread total time: {thread_total_time}")
    print(f"Process total time: {process_total_time}")
