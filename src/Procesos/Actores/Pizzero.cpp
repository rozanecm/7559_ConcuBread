//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Pizzero.h"

Pizzero::Pizzero(int id_pizzero) {
    this->canal_recepcionista = std::make_unique<FifoLectura>(ARCHIVO_FIFO_PIZZEROS);
    canal_recepcionista->abrir();
    id = "Pizzero " + std::to_string(id_pizzero);
}

Pizzero::~Pizzero(){
    std::cout << "destruyendo pizzero " + id << std::endl << std::flush;
    canal_recepcionista->cerrar();
}
