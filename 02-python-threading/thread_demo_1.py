from threading import Thread

def hello(idx):
    print(f"Hello from thread {idx}!")

if __name__ == "__main__":
    # create a list to hold the threads
    threads = []
    for i in range(10):
        # create a process
        thread = Thread(target=hello, args=(i,))
        # add the thread to the list
        threads.append(thread)

    # start all the processes
    for thread in threads:
        thread.start()
    
    # wait for all the processes to finish
    for thread in threads:
        thread.join()
