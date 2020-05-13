//
// Created by rozanecm on 5/12/20.
//

#include "Actor.h"

Actor::Actor() {
    canal.abrir();
}

Actor::~Actor() {
    canal.cerrar();
}

void Actor::mandar_msj_debug(std::string mensaje) {
    mensaje += "\n";
    canal.escribir(static_cast<const void *>(mensaje.c_str()), mensaje.length());
}
