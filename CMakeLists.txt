cmake_minimum_required(VERSION 3.0)

# Project configuration
project(timing-analysis)
set(SOURCES    src/main.cpp src/Channel.cpp)
set(EXECUTABLE timing_analysis)

# Executable
add_executable(${EXECUTABLE} ${SOURCES})

SET( CMAKE_CXX_COMPILER "/usr/bin/g++" )

# Configure compiler warnings
# if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang, AppleClang or GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")
# elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
#   # using Visual Studio C++
#   target_compile_definitions(${EXECUTABLE} PRIVATE _CRT_SECURE_NO_DEPRECATE)
#   set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
# endif()

if(MINGW)
    target_compile_definitions(${EXECUTABLE} PRIVATE __USE_MINGW_ANSI_STDIO=1)
endif()
