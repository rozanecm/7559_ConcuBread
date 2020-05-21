//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "DebugPrinter.h"
#include "../signals/SignalHandler.h"

#define DEBUG_FILE_PATH "../log_info.log"

DebugPrinter::DebugPrinter() {
    canal_debug.abrir();
    debug_file.open(DEBUG_FILE_PATH, std::ios::out | std::ios::trunc);
    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );
}

DebugPrinter::~DebugPrinter() {
    canal_debug.cerrar();
    debug_file.close();
    SignalHandler :: destruir ();
}

void DebugPrinter::atender_debug_msgs() {
    ssize_t bytesLeidos = 1;

    bool seguir_escuchando = true;
    while (sigint_handler.getGracefulQuit() == 0 and seguir_escuchando) {
        bytesLeidos = canal_debug.leer(static_cast<void *>(buffer), FIFO_DEBUG_BUFFSIZE);
        if (bytesLeidos > 0){
            std::string mensaje = buffer;
            mensaje.resize(bytesLeidos);
            this->print(mensaje);
        } else {
            seguir_escuchando = false;
        }
    }
}

void DebugPrinter::ejercer_tarea() {
    atender_debug_msgs();
}

void DebugPrinter::print(const std::string& msg) {
    debug_file << msg << std::flush;
}