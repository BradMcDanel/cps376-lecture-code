from threading import Thread

N = 100000
counter = 0

def buggy_sum():
    global counter
    for i in range(N):
        counter += 1

if __name__ == "__main__":
    # create a list to hold the threads
    threads = []
    for i in range(10):
        # create a thread
        thread = Thread(target=buggy_sum)
        # add the thread to the list
        threads.append(thread)

    # start all the processes
    for thread in threads:
        thread.start()
    
    # wait for all the processes to finish
    for thread in threads:
        thread.join()

    print(f"Counter: {counter}, should be {N * 10}")
