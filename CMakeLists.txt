cmake_minimum_required(VERSION 3.16)
project(ConcuBread)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConcuBread src/main.cpp src/ProcessManager.cpp src/ProcessManager.h src/DebugPrint.cpp src/DebugPrint.h src/enums.h)