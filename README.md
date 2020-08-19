<h1 aligh="center">VHTTP(Virya HTTP)</h1>
A minimalistic and fast http server, built in c++ and on boost library.

####Software Dependencies and Version Requirements

 - cmake version >= 3.3
 - boost version >= 1.74.0
 - GCC   version >= 4.7
 - MSVC  version >= 14.0

####Build


  1. clone the software from the repsoistory

    ```
https://github.com/bigvzhang/vhttp.git
    ```
  1. goto the repository and create the build directory and then cd it

    ```
cd ${TheRepsitory}
mkdir build
cd build
    ```
  1. use cmake to create projects and build
    - For windows, specify option -A with x64 to create a x64 solution or Win32 to create a Win32 solution. Then use nmake For example:

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
    - For windows, specify option -A with x64 to create a x64 solution or Win32 to create a Win32 solution. Then use nmake For example:
       ```
#if cmake fails to search boost dir, please set the following variable
#export BOOST_ROOT={boost install dir}
cmake ../cmake
make
       ```
