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
}

void Cocinero::ejercer_tarea() {
    std::cout << "cocinero ejerciendo" << std::endl;
    bool seguimos_recibiendo = true;
    while (sigint_handler.getGracefulQuit() == 0 and seguimos_recibiendo) {
        recibir_pedido(&seguimos_recibiendo);
        realizar_pedido();
        entregar_pedido_a_repartidor();
    }
    std::cout << "cocinero: termine" << std::endl;
}

void Cocinero::recibir_pedido(bool *seguir_recibiendo_pedidos) {
    ssize_t bytesLeidos = 0;
    this->id_pedido_actual = "";

    fcntl(canal_recepcionista->get_fd(), F_SETLKW, &(this->fl));
    while (bytesLeidos < FIFO_PEDIDOS_BUFFSIZE){
        bytesLeidos += canal_recepcionista->leer(static_cast<void *>(buffer), FIFO_PEDIDOS_BUFFSIZE);
        std::string mensaje = buffer;
        mensaje.resize(bytesLeidos);
        if(bytesLeidos == 0){
            *seguir_recibiendo_pedidos = false;
            break;
        }
        this->id_pedido_actual.append(mensaje);
    }
    fcntl(canal_recepcionista->get_fd(), F_SETLK, &(this->fl));
    mandar_msj_debug(id + ". Recibi pedido: " + this->id_pedido_actual);
}

void Cocinero::realizar_pedido() {
    std::cout << id << " realizando pedido " << id_pedido_actual << std::endl;
}

void Cocinero::entregar_pedido_a_repartidor() {
    std::cout << id << " entregando pedido " << id_pedido_actual << " a repartidor" << std::endl;
}
