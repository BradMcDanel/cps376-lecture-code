from multiprocessing import Process

def hello(idx):
    print(f"Hello from process {idx}!")

if __name__ == "__main__":
    # create a list to hold the processes
    processes = []
    for i in range(10):
        # create a process
        process = Process(target=hello, args=(i,))
        # add the process to the list
        processes.append(process)

    # start all the processes
    for process in processes:
        process.start()
    
    # wait for all the processes to finish
    for process in processes:
        process.join()
