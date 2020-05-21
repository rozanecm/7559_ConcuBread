#include <iostream>
#include <fstream>
#include "utils/ProcessManager.h"

#define ARCHIVO_CONFIG_PATH "../config.cb"

void leer_config_file(int *cant_panaderos, int *cant_pizzeros, int *cant_recepcionistas);

int main() {
    int cant_panaderos, cant_pizzeros, cant_recepcionistas;
    leer_config_file(&cant_panaderos, &cant_pizzeros, &cant_recepcionistas);

    std::cout << "Bienvenido a ConcuBread!" << std::endl;

    const std::unique_ptr<Proceso> &proceso_generado = ProcessManager::crear_procesos(cant_panaderos, cant_pizzeros,
                                                                                      cant_recepcionistas);
    proceso_generado->ejercer_tarea();
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
