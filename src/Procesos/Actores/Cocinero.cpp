//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Cocinero.h"

Cocinero::Cocinero() {
    this->fl.l_type = F_RDLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;

    canal_envio_pedidos_especialista_MM.abrir();
//    canal_recepcion_mm_especialista_MM.abrir();
}

Cocinero::~Cocinero() {
    canal_envio_pedidos_especialista_MM.cerrar();
//    canal_recepcion_mm_especialista_MM.cerrar();
}

void Cocinero::ejercer_tarea() {
    bool seguimos_recibiendo = true;
    while (sigint_handler.getGracefulQuit() == 0 and seguimos_recibiendo) {
        recibir_pedido(&seguimos_recibiendo);
        if (seguimos_recibiendo){
            realizar_pedido();
            entregar_pedido_a_repartidor();
        }
    }
    mandar_msj_debug(id + " termino con todos sus deberes.");
}

void Cocinero::recibir_pedido(bool *seguir_recibiendo_pedidos) {
    ssize_t bytesLeidos = 0;
    this->id_pedido_actual = "";

    fcntl(canal_recepcionista->get_fd(), F_SETLKW, &(this->fl));

    bytesLeidos += canal_recepcionista->leer(static_cast<void *>(buffer_recepcionista), FIFO_PEDIDOS_BUFFSIZE);

    fcntl(canal_recepcionista->get_fd(), F_SETLK, &(this->fl));

    if (bytesLeidos == 0) {
        *seguir_recibiendo_pedidos = false;
    } else {
        this->id_pedido_actual = buffer_recepcionista;
        mandar_msj_debug(id + ". Recibi pedido: " + this->id_pedido_actual);
    }
}

void Cocinero::realizar_pedido() {
    pedir_racion_mm();
    esperar_envio_mm();
    mandar_msj_debug(id + " realizando pedido " + id_pedido_actual);
    sleep(3);
    mandar_msj_debug(id + " termine de realizar el pedido " + id_pedido_actual);
}

void Cocinero::pedir_racion_mm() {
    mandar_msj_debug(id + " pidiendo racion de masa madre...");
    mandar_msj_fifo(id, &this->canal_envio_pedidos_especialista_MM);
}

void Cocinero::esperar_envio_mm() {
//    TODO esperar envio
    mandar_msj_debug(id + " recibi racion de masa madre! Continuemos con el pedido...");
}

void Cocinero::entregar_pedido_a_repartidor() {
    mandar_msj_debug(id + " entregando pedido " + id_pedido_actual + " a repartidor.");
}
