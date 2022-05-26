# OpenMP

## Installation
1. CMakeList.txt
```cmake=
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${MY_EXECUTABLE} PUBLIC OpenMP::OpenMP_CXX)
endif()
```
> 注意 CMake 版本必須 >= 3.9

2. Make sure your mingw has install OpenMP plugin

![](https://i.imgur.com/DitIi7Z.png)

> If you are using MSVC to be the compiler, then ignore this.  

3. Include `<omp.h>` header file

4. Enjoy!

------------------------------------------------------------
Written by ThIsJaCk (2022).