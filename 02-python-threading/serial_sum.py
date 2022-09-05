import time
MAX_VALUE = 2**24

def sum_range(min, max):
    list_sum = 0
    for i in range(min, max):
        list_sum += i

    return list_sum


if __name__ == "__main__":
    start = time.time()
    result = sum_range(0, MAX_VALUE)
    end = time.time()
    total_time = end - start
    print(f"Sum: {result}, time: {total_time}")
