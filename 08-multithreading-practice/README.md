## Build instructions

```
# first navigate to 08-multithreading-practice/ directory
mkdir build
cd build
cmake ..
make

# now, all executables have been built.
# if you modify any cpp file, you need to re-run make (cmake .. does not need to be re-run)

# type `ls` to see all the executables (one per .cpp file in src/)
ls
```


## Working through this code
Write down your answers as you go.
1. Run `./queue_example` and look at the code to make sure you understand what it is doing.
    a. Discuss the changes would you need to make to sum **all** values across all of the consumers.
    b. Modify `queue_example.cpp` to makes these changes.
2. Implement `find_string.cpp`. This is the serial version of the Question 2 of last quiz.
3. Implement `threaded_find_string.cpp`. I have provided some starter code for you. Think about what each thread needs to do in this case.
4. **discussion time**
5. Implement `dining.cpp`, which is the Dining Philosophers problems we dicussed.
