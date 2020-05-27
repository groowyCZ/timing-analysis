cmake_minimum_required(VERSION 3.10)

project(timing-analysis)

add_executable(timing-analysis
               src/main.cpp
               src/Channel.cpp

               headers/AudioFile.h
               headers/Channel.h)

target_include_directories(timing-analysis
                           PRIVATE
                           headers)

