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
    switch (ProcessManager::crear_procesos(PANADEROS, PIZZEROS, RECEPCIONISTAS)) {
        case Padre:
            std::cout << "soy padre" << std::endl;
            break;
        case MtroPanadero:
            std::cout << "soy un panadero" << std::endl;
            break;
        case MtroPizzero:
            std::cout << "soy un pizzero" << std::endl;
            break;
        case Recepcionista:
            std::cout << "soy un recepcionista" << std::endl;
            break;
        case EspecialistaMasaMadre:
            std::cout << "soy el especialista MM" << std::endl;
            break;
    }
sleep(1);
    return 0;
}
