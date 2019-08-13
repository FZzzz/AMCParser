# AMCParser
A Parser for ASF/AMC motion capture data. 

## Introduction
This library is written in `c++1x`. And its output is a character with `Name-BoneData` STL map.
Inside the character, it saves all information parsed out from AMC/ASF files.

## How to use?
Put all files into your project and compile.
Please refer to `main.cpp` and `Makefile` for details. 
```
I didn't put GLM in this repository. If you want to use `Makefile`, please remember to include GLM by yourself 
```

## Dependency
GLM

