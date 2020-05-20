//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Pizzero.h"

Pizzero::Pizzero(int id_pizzero) {
    this->canal_recepcionista = std::make_unique<FifoLectura>(ARCHIVO_FIFO_PIZZEROS);
    canal_recepcionista->abrir();

    set_id(id_pizzero);

}

void Pizzero::set_id(int id_pizzero) {
    id = "Piz";
    if(id_pizzero < 10){
        id.append("0");
    }
    id.append(std::to_string(id_pizzero));
}

Pizzero::~Pizzero(){
    canal_recepcionista->cerrar();
}
