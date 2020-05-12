#include <iostream>
#include <unistd.h>
#include "ProcessManager.h"
#include "enums.h"
#include "DebugPrint.h"
#include "fifos/FifoLectura.h"
#include "fifos/FifoEscritura.h"
#include "signals/SIGINT_Handler.h"
#include "signals/SignalHandler.h"
#include <fstream>

//#define PANADEROS 5
//#define PIZZEROS 1
//#define RECEPCIONISTAS 1

#define ARCHIVO_CONFIG_PATH "../config.cb"

#define BUFFSIZE 100
#define ARCHIVO_FIFO "/tmp/archivo_fifo"

void leer_config_file(int *cant_panaderos, int *cant_pizzeros, int *cant_recepcionistas);

int main() {
    int cant_panaderos, cant_pizzeros, cant_recepcionistas;
    leer_config_file(&cant_panaderos, &cant_pizzeros, &cant_recepcionistas);

    std::cout << "Bienvenido a ConcuBread!" << std::endl;
    std::cout << "Pid padre: " << getpid() << std::endl;
    DebugPrint debug_printer;
    switch (ProcessManager::crear_procesos(cant_panaderos, cant_pizzeros, cant_recepcionistas, &debug_printer)) {
        case Padre: {
            debug_printer.print("Sample debug print.");
            std::cout << "soy padre con pid: " << getpid() << std::endl;
            // event handler para la senial SIGINT (-2)
            SIGINT_Handler sigint_handler;

            // se registra el event handler declarado antes
            SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

            FifoLectura canal ( ARCHIVO_FIFO );
            char buffer[BUFFSIZE];
            canal.abrir();

            // mientras no se reciba la senial SIGINT, el proceso realiza su trabajo
            ssize_t bytesLeidos = 1;

            while (sigint_handler.getGracefulQuit() == 0
//            and bytesLeidos > 0
            ) {
                bytesLeidos = canal.leer(static_cast<void *>(buffer), BUFFSIZE);
                if (bytesLeidos > 0){
                    std::string mensaje = buffer;
                    mensaje.resize(bytesLeidos);
                    debug_printer.print(mensaje);
                }
            }
            // se recibio la senial SIGINT, el proceso termina
            SignalHandler :: destruir ();

            canal.cerrar();
            std::cout << "soy padre y estoy saliendo. Salu3!" << std::endl;
            break;
        }
        case MtroPanadero: {
            debug_printer.print("saluda el mtro panadero!");
            FifoEscritura canal(ARCHIVO_FIFO);
            std::string mensaje = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the.";

            canal.abrir();
//            sleep(5);
            canal.escribir(static_cast<const void *>(mensaje.c_str()), mensaje.length());
            std::cout << "[Escritor] Escribi el mensaje " << mensaje << " en el fifo" << std::endl;

            std::cout << "soy un panadero" << std::endl;
            break;
        }
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
