#include <iostream>
#include <unistd.h>
#include "ProcessManager.h"
#include "enums.h"
#include "DebugPrint.h"

#define PANADEROS 5
#define PIZZEROS 1
#define RECEPCIONISTAS 1

int main() {
    std::cout << "Bienvenido a ConcuBread!" << std::endl;
    std::cout << "Pid padre: " << getpid() << std::endl;
    if (ProcessManager::crear_panaderos(PANADEROS) == Padre){
        std::cout << "Padre after panaderos creation from pid " << getpid() << std::endl;
        sleep(1);
    } else {
//        DebugPrint::print("Hijo after panaderos creation from pid " + std::to_string(getpid()));
        std::cerr << "Hijo after panaderos creation from pid " << getpid() << std::endl;
    }
    return 0;
}
