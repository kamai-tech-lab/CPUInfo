# CPUInfo
Provides a function to obtain internal information of x86 series CPUs using the CPUID instruction.

The requirements are:

* CMake 3.11 or better
* C++ compiler (MSVC, gcc, clang and more)


To configure:
```
cmake -S . -B build
```

To build:
```
cmake --build build
```

To use an IDE, such as MSVC
```
cmake -S . -B build -G "Visual Strudio 16 2019"
cmake --open build
```
