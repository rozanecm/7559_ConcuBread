//
// Created by rozanecm on 5/12/20.
//

#include "Actor.h"

#include <utility>
#include <iostream>

Actor::Actor() {
    canal_debug.abrir();
}

Actor::~Actor() {
    canal_debug.cerrar();
}

void Actor::mandar_msj_fifo(std::string mensaje, FifoEscritura *fifo) {
    fifo->escribir(static_cast<const void *>(mensaje.c_str()),
                   mensaje.length());
}

void Actor::mandar_msj_debug(std::string mensaje) {
    mensaje += "\n";
    mandar_msj_fifo(std::move(mensaje), &canal_debug);
}
