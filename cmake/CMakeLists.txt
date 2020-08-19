cmake_minimum_required(VERSION 3.3 FATAL_ERROR) # Boost_1_74_0 requires?
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(vhttp C CXX)
cmake_policy(SET CMP0057 NEW)   # Boost_1_74_0 requires the policy

if (WIN32)
    ############################################################################
    #Notice: Using cmake command option -A x64 to generate x64 VS project files!
    #        The following three lines failed to configure x64 architecture:
    #set(CMAKE_VS_PLATFORM_NAME_DEFAULT, "x64") 
    #set(CMAKE_CXX_COMPILER_ARCHITECTURE_ID, "x64")
    #set(CMAKE_GENERATOR_PLATFORM, "x64")
    ############################################################################

    ############################################################################
    #Notice: Using environment variables BOOST_INCLUDEDIR AND BOOST_LIBRARY to
    #        configure boost.
    #set(BOOST_ROOT "D:/MyLib/boost_1_74_0")
    #set(BOOST_INCLUDEDIR "D:/MyLib/boost_1_74_0")
    #set(BOOST_LIBRARYDIR "D:/MyLib/boost_1_74_0/lib64-msvc-14.0")
    ############################################################################

    # use static libraries on windows
    set(Boost_USE_STATIC_LIBS TRUE)
else()
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_package(Threads REQUIRED)
endif()

SET (SRCDIR ../src_cpp)


#list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(Boost 1.74.0 COMPONENTS filesystem thread chrono)
if(Boost_FOUND)
    message("OK: Found Boost")
    include_directories(${Boost_INCLUDE_DIRS}) 
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
else()
    #message("Error: Could NOT find Boost!")
    return (101)
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
   add_definitions(-Wno-unknown-pragmas -Wno-write-strings -Wno-terminate)

   execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_GREATER 6.1 OR GCC_VERSION VERSION_EQUAL 6.1)
        message(STATUS "C++14 activated.")
        add_definitions("-std=gnu++14")
   elseif (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "C++11 activated.")
        add_definitions("-std=gnu++11")
   elseif(GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
        message(WARNING "C++0x activated. If you get any errors update to a compiler which fully supports C++11")
        add_definitions("-std=gnu++0x")
   else ()
        message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")
   endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

if(Boost_FOUND)
   message("   Thread=>" ${CMAKE_THREAD_LIBS_INIT})
   message("Boost Lib=>" ${Boost_LIBRARIES})
   message("Boost Inc=>" ${Boost_INCLUDE_DIRS}  )
else()
   message("Library Missed" )
endif()

add_executable(vhttp 
        ${SRCDIR}/main.cpp
        ${SRCDIR}/vhttp_funcs.cpp
        ${SRCDIR}/virya_common.cpp
    )
target_link_libraries(vhttp ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


