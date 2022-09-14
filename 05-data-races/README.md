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
