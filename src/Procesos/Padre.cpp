//
// Created by rozanecm on 5/12/20.
//

#include "Padre.h"
#include "../signals/SignalHandler.h"

Padre::Padre() {
    canal.abrir();

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );
}

Padre::~Padre() {
    canal.cerrar();
    SignalHandler :: destruir ();
}

void Padre::atender_hijos(DebugPrint *debug_printer) {
    ssize_t bytesLeidos = 1;

    while (sigint_handler.getGracefulQuit() == 0
//            and bytesLeidos > 0
            ) {
        bytesLeidos = canal.leer(static_cast<void *>(buffer), FIFO_BUFFSIZE);
        if (bytesLeidos > 0){
            std::string mensaje = buffer;
            mensaje.resize(bytesLeidos);
            debug_printer->print(mensaje);
        }
    }
}
