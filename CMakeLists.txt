cmake_minimum_required(VERSION 3.16)
project(ConcuBread)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConcuBread src/main.cpp src/utils/ProcessManager.cpp src/utils/ProcessManager.h src/utils/DebugPrint.cpp src/utils/DebugPrint.h src/utils/enums.h src/fifos/Fifo.cpp src/fifos/Fifo.h src/fifos/FifoEscritura.cpp src/fifos/FifoLectura.cpp src/fifos/FifoLectura.h src/signals/EventHandler.h src/signals/SIGINT_Handler.h src/signals/SignalHandler.cpp src/signals/SignalHandler.h)