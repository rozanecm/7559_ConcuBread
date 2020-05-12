//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Actor.h"

Actor::Actor() {
    canal.abrir();
}

Actor::~Actor() {
    canal.cerrar();
}

void Actor::mandar_msj_debug(const std::string &mensaje) {
//    std::cout << "por mandar msg de long: " << mensaje.length() << std::endl;
    canal.escribir(static_cast<const void *>(mensaje.c_str()), mensaje.length());
}
