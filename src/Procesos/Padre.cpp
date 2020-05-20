//
// Created by rozanecm on 5/12/20.
//

#include "Padre.h"
#include "../signals/SignalHandler.h"

Padre::Padre() {
    canal_debug.abrir();

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );
}

Padre::~Padre() {
    canal_debug.cerrar();
    SignalHandler :: destruir ();
}

void Padre::atender_hijos() {
    ssize_t bytesLeidos = 1;

    while (sigint_handler.getGracefulQuit() == 0
//    TODO ver esta condicion
//            and bytesLeidos > 0
            ) {
        bytesLeidos = canal_debug.leer(static_cast<void *>(buffer), FIFO_DEBUG_BUFFSIZE);
        if (bytesLeidos > 0){
            std::string mensaje = buffer;
            mensaje.resize(bytesLeidos);
            debug_printer.print(mensaje);
        }
    }
}

void Padre::ejercer_tarea() {
    debug_printer.print("Soy el padre con pid " + std::to_string(getpid()) + '\n');
    atender_hijos();
}
