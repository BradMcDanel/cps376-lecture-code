## Build instructions

```
# first navigate to 05-data-races/ directory
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
1. Run `./race` in your `build/` directory (try running it a few times). What do you observe?
   * Look at the code and try to figure out what is going on 
2. Now run `./mutex_example` a few times. This is similar to `race`, but there are some differences. Do you see the same output?
   * Stop here - we will talk about the next part together
3. Open `src/mutex_impl.cpp` and try figure out how it works. Why would this type of code fix the issue we saw in `race`?
4. Now, run `./sum_serial` and check the implementation in `sum_serial.cpp`. This is the same problem we looked at in python before.
5. Using the other examples, try to finish the implementation of `sum_parallel.cpp`.
   * My solution is provided in `sum_parallel_sol.cpp` that you can refer to after class.
