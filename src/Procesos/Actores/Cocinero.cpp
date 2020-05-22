//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include <random>
#include "Cocinero.h"

Cocinero::Cocinero() {
    this->fl.l_type = F_RDLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;

    canal_envio_pedidos_especialista_MM.abrir();
}

Cocinero::~Cocinero() {
    canal_envio_pedidos_especialista_MM.cerrar();
    canal_recepcion_de_mm->cerrar();
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
//        TODO resize string
        mandar_msj_debug(id + ". Recibi pedido: " + this->id_pedido_actual);
    }
}

void Cocinero::realizar_pedido() {
    /* Inicializacion random */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    pedir_racion_mm();
    esperar_envio_mm();
    mandar_msj_debug(id + " realizando pedido " + id_pedido_actual);
    sleep(dis(gen));
    mandar_msj_debug(id + " termine de realizar el pedido " + id_pedido_actual);
}

void Cocinero::pedir_racion_mm() {
    mandar_msj_debug(id + " pidiendo racion de masa madre...");
    mandar_msj_fifo(id, &this->canal_envio_pedidos_especialista_MM);
}

void Cocinero::esperar_envio_mm() {
    abrir_canal_recepcion_de_mm();
    std::string mensaje;
    canal_recepcion_de_mm->leer(static_cast<void *>(buffer_recepcion_mm), LENGTH_MSJ_ENVIO_MM);
    mensaje = buffer_recepcion_mm;
    mensaje.resize(LENGTH_MSJ_ENVIO_MM);
    if(mensaje == MENSAJE_PARA_ENVIAR_MM_A_COCINEROS){
        mandar_msj_debug(id + " recibi racion de masa madre! Continuemos con el pedido...");
    } else{
        mandar_msj_debug("ALERTA! " + id + " Por alguna razon no recibi racion masa madre y puedo seguir igual...");
        std::cout << "msj recibido en lugar de mm: " << mensaje << std::endl;
        mandar_msj_debug("msj recibido en lu    gar de mm: " + std::to_string(int(buffer_recepcion_mm[1])));
    }
}

void Cocinero::entregar_pedido_a_repartidor() {
    mandar_msj_debug(id + " entregando pedido " + id_pedido_actual + " a repartidor.");
}

void Cocinero::abrir_canal_recepcion_de_mm() {
    if(not canal_recepcion_de_mm_fue_abierto){
        canal_recepcion_de_mm = std::make_unique<FifoLectura>(id);
        canal_recepcion_de_mm->abrir();
        canal_recepcion_de_mm_fue_abierto = true;
    }
}
