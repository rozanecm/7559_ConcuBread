//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "EspecialistaMasaMadre.h"


EspecialistaMasaMadre::EspecialistaMasaMadre() {
    canal_cocineros.abrir();
}

EspecialistaMasaMadre::~EspecialistaMasaMadre() {
    canal_cocineros.cerrar();
//    cerrar_canales_particulares();
}

void EspecialistaMasaMadre::ejercer_tarea() {
    bool seguir_recibiendo_pedidos = true;
    while (seguir_recibiendo_pedidos) {
        std::string id_pedido = escuchar_pedidos(&seguir_recibiendo_pedidos);
        if(seguir_recibiendo_pedidos) {
            mandar_msj_debug("Especialista: recibi pedido de racion de MM: " + id_pedido);
            entregar_pedido(id_pedido);
        }
    }
}

std::string EspecialistaMasaMadre::escuchar_pedidos(bool *seguir_recibiendo_pedidos) {
    ssize_t bytesLeidos = 0;
    std::string id_pedido_actual;

    while (bytesLeidos < FIFO_ESPECIALISTA_MM_BUFFSIZE){
        bytesLeidos += canal_cocineros.leer(static_cast<void *>(buffer), FIFO_ESPECIALISTA_MM_BUFFSIZE);
        std::string mensaje = buffer;
        mensaje.resize(bytesLeidos);
        if(bytesLeidos == 0){
            *seguir_recibiendo_pedidos = false;
            break;
        }
        id_pedido_actual.append(mensaje);
    }
    return id_pedido_actual;
}

void EspecialistaMasaMadre::entregar_pedido(const std::string& id_pedido) {
    check_existencia_canal(id_pedido);
//    TODO enviar racion mm
}

void EspecialistaMasaMadre::check_existencia_canal(const std::string &id_pedido) {
    /**
     * Este metodo se encarga de abrir un fifo nuevo, en caso que aun no exista, para el cocinero
     * a quien le debe enviar una racion de MM
     * */
}

void EspecialistaMasaMadre::cerrar_canales_particulares() {
}
