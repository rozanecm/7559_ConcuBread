cmake_minimum_required(VERSION 3.16)
project(ConcuBread)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConcuBread src/main.cpp src/ProcessManager.cpp src/ProcessManager.h src/DebugPrint.cpp src/DebugPrint.h src/enums.h src/fifos/Fifo.cpp src/fifos/Fifo.h src/fifos/FifoEscritura.cpp src/fifos/FifoLectura.cpp src/fifos/FifoLectura.h src/signals/EventHandler.h src/signals/SIGINT_Handler.h src/signals/SignalHandler.cpp src/signals/SignalHandler.h)