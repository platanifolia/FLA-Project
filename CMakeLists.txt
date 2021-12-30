cmake_minimum_required(VERSION 3.0)
project(FLA-Project)
set(CMAKE_CXX_STANDARD 11)

add_executable( turing turing-project/main.cc 
                turing-project/stringhandle.h turing-project/stringhandle.cc
                turing-project/turingmachine.h turing-project/turingmachine.cc)
