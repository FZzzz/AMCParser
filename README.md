# AMCParser
A Parser for ASF/AMC motion capture data. 

## Introduction
This library is written in `c++1x`, and mostly follows Google C++ coding style [guide](https://google.github.io/styleguide/cppguide.html). And the parser outputs a character with `BoneName-Keyframes` STL map. Inside the character, it saves all information parsed out from AMC/ASF files.

## How to use?
Put all `.h`, `.cpp` files into your project and compile.
Please refer to `main.cpp` and `Makefile` for details. 
```
I didn't put GLM in this repository. Please remember to include GLM!! 
```

## Dependency
GLM

