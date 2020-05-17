//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Panadero.h"

Panadero::Panadero(int id_panadero){
    this->canal_recepcionista = std::make_unique<FifoLectura>(ARCHIVO_FIFO_PANADEROS);
    canal_recepcionista->abrir();
    id = "Panadero " + std::to_string(id_panadero);
}

Panadero::~Panadero() {
    canal_recepcionista->cerrar();
}
