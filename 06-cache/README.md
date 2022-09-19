## Build instructions

```
# first navigate to 06-memory/ directory
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
1. Run `./iter_comp` 3 times. Record (roughly) average runtime for vector and list. Which is faster? Try to think of why this is the case.
2. Run `./alloc_comp N` where N is multiple sizes (try values in the range of 100000 to 10000000). Again, write down the times and which is faster. Why is one faster?
3. Run `./cache_miss` and record the time differences. Look at the code and try to understand the different. What is the speed-up ratio you get here?
4. **discussion time**
5.  Look at `src/game_example.cpp`. Run the code (`./game_example`) and then figure out how to implement what is described. If done correctly, you should see some speedup.
