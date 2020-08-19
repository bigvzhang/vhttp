# VHTTP - Virya HTTP
A minimalistic and fast http server, built in c++ and on boost library.

#### Software Dependencies and Version Requirements
 - cmake version >= 3.3
 - boost version >= 1.74.0
 - GCC   version >= 4.7
 - MSVC  version >= 14.0

#### Build
  1. clone the software from the repsoistory

```
git clone https://github.com/bigvzhang/vhttp.git
```
  1. goto the repository and create the build directory and then cd it

    ```
cd ${TheRepsitory}
mkdir build
cd build
```
  1. use cmake to create projects and build
    * For windows, specify option -A with x64 to create a x64 solution or Win32 to create a Win32 solution. Then use nmake For example:
       ```
REM if cmake fails to search boost dir, please set the following variables
REM SET BOOST_INCLUDEDIR={boost header dir}
REM SET BOOST_LIBRARYDIR={boost library dir}
REM SET PATH=%PATH%;{PATH_TO_CMAKE}
REM SETUP VC Enviroment, like:
REM "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat"
REM create solution
cmake ..\cmake -A x64
REM Build
MSBuild vhttp.sln /p:Configuration=Release;Platform=x64

```
    * For Linux, run cmake and then make

       ```
#if cmake fails to search boost dir, please set the following variable
#export BOOST_ROOT={boost install dir}
cmake ../cmake
make
```

#### Run
   ```
Usage: vhttp <address> <port> <doc_root> <threads>
Example:
    vhttp 0.0.0.0 8080 . 1
```

#### Files
  | File                         | Description                                |
  | :--------------------------- | :----------------------------------------- |
  |src_cpp/main.cpp              | create server                              |
  |src_cpp/range_file_body.hpp   | functions to create range file body        |
  |src_cpp/vhttp_funcs.h         | functions to parse http requests           |
  |src_cpp/vhttp_funcs.cpp       |                                            |
  |src_cpp/virya_common.h        | functions to operate io, strings & etc     |
  |src_cpp/vhttp_common.h        |                                            |
  |src_cpp/virya_common.cpp      |                                            |
  |cmake/CMakeLists.txt          | cmake file                                 |
  |LICENSE.txt                   |                                            |
  |README.md                     |                                            |
