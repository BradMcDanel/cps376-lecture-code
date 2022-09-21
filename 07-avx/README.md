## Build instructions

```
# first navigate to 07-avx/ directory
mkdir build
cd build
cmake ..
make

# now, all executables have been built.
# if you modify any cpp file, you need to re-run make (cmake .. does not need to be re-run)

# type `ls` to see all the executables (one per .cpp file in src/)
ls
```

Open up the AVX instrinsics guide, so you can search for instructions as you look at the code: https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

## Working through this code
Write down your answers as you go.
1. Run `./avx_example` and then go look at the program. How many elements are being multipled in this case? What types and/or functions do you have questions about?
2. Look at `sum_avx.cpp`. Your goal is to implement the `sum_avx_256` function in this file. Refer back to `avx_example.cpp` for some help as you try to think about how to solve the problem.
