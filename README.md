# Using CMake with gcov

After cloning this directory, an "out-of-source build" is recommended to
test the project. To perform an out-of-source build, run the following commands
from the project root directory:

```
mkdir build
cd build
cmake ..
```

From the build directory you may build the project using `make`. The coverage
files from gcov can be generated using `make gcov`. A summary of the two source
files will be output and stored in `build/coverage/TestHello.tmp`. Running
`make clean` will remove the enitre coverage directory.
