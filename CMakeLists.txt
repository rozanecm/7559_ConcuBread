cmake_minimum_required(VERSION 3.16)
project(ConcuBread)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConcuBread main.cpp ProcessManager.cpp ProcessManager.h DebugPrint.cpp DebugPrint.h enums.h)