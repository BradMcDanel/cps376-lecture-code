import time
import sys
from multiprocessing import Process, Queue
MAX_VALUE = 2**24

# :::WARNING:::
# Don't look at this unless you are stuck or want to compare implementations!!!

def sum_range(min, max, queue):
    list_sum = 0
    for i in range(min, max):
        list_sum += i

    # add to result queue
    queue.put(list_sum)

if __name__ == "__main__":
    num_processes = int(sys.argv[1])

    # create a list to hold the processes
    processes = []
    # create queue to hold the results
    queue = Queue()
    for i in range(num_processes):
        start_idx = i * MAX_VALUE // num_processes
        end_idx = (i + 1) * MAX_VALUE // num_processes
        # create a process
        process = Process(target=sum_range, args=(start_idx, end_idx, queue))
        # add the process to the list
        processes.append(process)

    start = time.time()
    # start all the processes
    for process in processes:
        process.start()
    
    # wait for all the processes to finish
    for process in processes:
        process.join()

    result = 0
    # get the results from the queue
    for i in range(num_processes):
        result += queue.get()

    end = time.time()
    total_time = end - start

    print(f"Sum: {result}, time: {total_time}")
