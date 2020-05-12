#include <iostream>
#include <unistd.h>
#include "utils/ProcessManager.h"
#include "utils/enums.h"
#include "utils/fifo_consts.h"
#include "utils/DebugPrint.h"
#include "fifos/FifoLectura.h"
#include "fifos/FifoEscritura.h"
#include "signals/SIGINT_Handler.h"
#include "signals/SignalHandler.h"
#include "Actores/Panadero.h"
#include "Actores/Pizzero.h"
#include "Actores/Recepcionista.h"
#include "Actores/EspecialistaMasaMadre.h"
#include "Padre.h"
#include <fstream>

//#define PANADEROS 5
//#define PIZZEROS 1
//#define RECEPCIONISTAS 1

#define ARCHIVO_CONFIG_PATH "../config.cb"

//#define FIFO_BUFFSIZE 100
//#define ARCHIVO_FIFO "/tmp/archivo_fifo"

void leer_config_file(int *cant_panaderos, int *cant_pizzeros, int *cant_recepcionistas);

int main() {
    int cant_panaderos, cant_pizzeros, cant_recepcionistas;
    leer_config_file(&cant_panaderos, &cant_pizzeros, &cant_recepcionistas);

    std::cout << "Bienvenido a ConcuBread!" << std::endl;
    DebugPrint debug_printer;
    debug_printer.print("Soy padre con pid " + std::to_string(getpid()) + '\n');

    switch (ProcessManager::crear_procesos(cant_panaderos, cant_pizzeros, cant_recepcionistas, &debug_printer)) {
        case Padre: {
            class Padre padre;
            padre.atender_hijos(&debug_printer);
            std::cout << "soy padre y estoy saliendo. Salu3!" << std::endl;
            break;
        }
        case MtroPanadero: {
            Panadero panadero;
            panadero.mandar_msj_debug("Debug msg from panadero\n");

            break;
        }
        case MtroPizzero: {
            Pizzero pizzero;
            pizzero.mandar_msj_debug("Debug msg from pizzero\n");
            break;
        }
        case Recepcionista: {
            class Recepcionista recepcionista;
            recepcionista.mandar_msj_debug("Debug msg from recepcionista\n");
            break;
        }
        case EspecialistaMasaMadre:{
            class EspecialistaMasaMadre especialista;
            especialista.mandar_msj_debug("Debug msg from especialista MM!\n");
            break;
        }
    }
    return 0;
}

void leer_config_file(int *cant_panaderos, int *cant_pizzeros, int *cant_recepcionistas) {
    std::ifstream config_file(ARCHIVO_CONFIG_PATH);
    if (config_file.is_open()){
        std::string line;
        try{
            std::getline(config_file, line);
            *cant_panaderos = std::stoi(line);

            std::getline(config_file, line);
            *cant_pizzeros = std::stoi(line);

            std::getline(config_file, line);
            *cant_recepcionistas = std::stoi(line);
        } catch (std::exception const & ex) {
            std::cout << "Error reading config file. Please check config file format and try again." << std::endl;
            config_file.close();
            exit(0);
        }
        config_file.close();
    } else {
        std::cout << "No config file found! Please, verify the config file is present and try again." << std::endl;
        exit(0);
    }
}
