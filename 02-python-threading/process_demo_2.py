from multiprocessing import Process, Queue

def elementwise_product(x, y, queue):
    result = []
    for i in range(len(x)):
        result.append(x[i] * y[i])

    # we can't return the result, so we add it to the queue
    # this is kind of annoying, but such is life with multiprocessing
    queue.put(result)


if __name__ == "__main__":
    x = [i for i in range(100)]
    y = [i for i in range(100)]
    N = 2

    # create a list to hold the processes
    processes = []  

    # create queue to hold the results (this is doing some magic for us)
    queue = Queue()

    for i in range(N):
        # split the data into N chunks
        start_idx = i * len(x) // N
        end_idx = (i + 1) * len(x) // N

        # create a process
        process = Process(target=elementwise_product,
                          args=(x[start_idx:end_idx], y[start_idx:end_idx], queue))

        # add the process to the list
        processes.append(process)

    # start all the processes
    for process in processes:
        process.start()
    
    # wait for all the processes to finish
    for process in processes:
        process.join()

    result = []
    # get the results from the queue
    for i in range(N):
        result += queue.get()
    
    print(result)
