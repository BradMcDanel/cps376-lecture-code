import time
import sys
from multiprocessing import Process, Queue
MAX_VALUE = 2**24

"""
Parallelize the serial_sum.py program using multiprocessing.
Refer to the process_demo_2.py program for help.
My solution is in parallel_sum_sol.py. (Don't look at it unless you are stuck or want to compare implementations!!!)
"""

if __name__ == "__main__":
    # number of processes should be specified as a command line argument
    # e.g., "python3 parallel_sum.py 4" would use 4 processes
    # once working: try running with 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024
    #               what runtimes do you observe as you increase the number of processes? 
    num_processes = int(sys.argv[1])
