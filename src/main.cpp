#include <iostream>
#include <fstream>
#include <cstring>
#include "utils/ProcessManager.h"

#define ARCHIVO_CONFIG_PATH "../config.cb"

void leer_config_file(int *cant_panaderos, int *cant_pizzeros,
                      int *cant_recepcionistas);

bool print_debug_msgs(int argc, char **argv);

int main(int argc, char *argv[]) {
    int cant_panaderos, cant_pizzeros, cant_recepcionistas;
    leer_config_file(&cant_panaderos, &cant_pizzeros, &cant_recepcionistas);

    std::cout << "Bienvenido a ConcuBread!" << std::endl;
    std::cout << "Simulando..." << std::endl;

    const std::unique_ptr<Proceso> &proceso_generado =
            ProcessManager::crear_procesos(
                    cant_panaderos, cant_pizzeros,
                    cant_recepcionistas,
                    print_debug_msgs(argc, argv));
    proceso_generado->ejercer_tarea();
    return 0;
}

bool print_debug_msgs(int argc, char **argv) {
    if (argc > 1) {
        if (std::strcmp(argv[1], "--print-debug") == 0) {
            if (std::strcmp(argv[2], "false") == 0) {
                std::cout << "Setting debug printing off..." << std::endl;
                return false;
            }
            if (std::strcmp(argv[2], "true") == 0) {
                std::cout << "Setting debug printing on..." << std::endl;
                return true;
            }
        }
        std::cout << "Unidentified arg name. Debug printing set on as default."
                  << std::endl;
        return true;
    }
    /* si no se especifica nada... */
    return true;
}

void leer_config_file(int *cant_panaderos, int *cant_pizzeros,
                      int *cant_recepcionistas) {
    std::ifstream config_file(ARCHIVO_CONFIG_PATH);
    if (config_file.is_open()) {
        std::string line;
        try {
            std::getline(config_file, line);
            *cant_panaderos = std::stoi(line);

            std::getline(config_file, line);
            *cant_pizzeros = std::stoi(line);

            std::getline(config_file, line);
            *cant_recepcionistas = std::stoi(line);
        } catch (std::exception const &ex) {
            std::cout
                    << "Error reading config file."
                       " Please check config file format and try again."
                    << std::endl;
            config_file.close();
            exit(0);
        }
        config_file.close();
    } else {
        std::cout
                << "No config file found!"
                   " Please, verify the config file is present and try again."
                << std::endl;
        exit(0);
    }
}
