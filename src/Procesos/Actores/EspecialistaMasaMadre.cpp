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
    canal_cocineros.eliminar();
    cerrar_canales_particulares();
}

void EspecialistaMasaMadre::ejercer_tarea() {
    bool seguir_recibiendo_pedidos = true;
    while (sigint_handler.getGracefulQuit() == 0 and seguir_recibiendo_pedidos) {
        std::string id_solicitante = escuchar_pedidos(
                &seguir_recibiendo_pedidos);
        if (seguir_recibiendo_pedidos) {
            mandar_msj_debug("Especialista: recibi pedido de racion de"
                             " MM de parte de: " + id_solicitante);
            entregar_pedido(id_solicitante);
        }
    }
}

std::string EspecialistaMasaMadre::escuchar_pedidos(bool *
seguir_recibiendo_pedidos) {
    ssize_t bytesLeidos = 0;
    std::string id_solicitante_actual;

    while (bytesLeidos < FIFO_ESPECIALISTA_MM_BUFFSIZE) {
        bytesLeidos += canal_cocineros.leer(static_cast<void *>(buffer),
                                            FIFO_ESPECIALISTA_MM_BUFFSIZE);
        std::string mensaje = buffer;
        mensaje.resize(bytesLeidos);
        if (bytesLeidos == 0) {
            *seguir_recibiendo_pedidos = false;
            break;
        }
        id_solicitante_actual.append(mensaje);
    }
    return id_solicitante_actual;
}

void EspecialistaMasaMadre::entregar_pedido(const std::string &id_solicitante) {
    obtener_canal_envio_mm(id_solicitante)->escribir(
            MENSAJE_PARA_ENVIAR_MM_A_COCINEROS, LENGTH_MSJ_ENVIO_MM);
}

bool
EspecialistaMasaMadre::existe_canal_envio_mm(const std::string &id_pedido) {
    for (auto &it : canales_envio_mm) {
        if (it.first == id_pedido) {
            return true;
        }
    }
    return false;
}

FifoEscritura *EspecialistaMasaMadre::obtener_canal_envio_mm(
        const std::string &id_solicitante) {
    if (not existe_canal_envio_mm(id_solicitante)) {
        canales_envio_mm.push_back(std::make_pair(id_solicitante,
                                                  new FifoEscritura(
                                                          id_solicitante)));
        canales_envio_mm.back().second->abrir();
        return canales_envio_mm.back().second;
    }
    for (auto &it : canales_envio_mm) {
        if (it.first == id_solicitante)
            return it.second;
    }
}

void EspecialistaMasaMadre::cerrar_canales_particulares() {
    for (auto &it : canales_envio_mm) {
        it.second->cerrar();
        it.second->eliminar();
        delete it.second;
    }
    canales_envio_mm.clear();
}
