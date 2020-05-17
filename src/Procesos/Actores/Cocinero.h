//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_COCINERO_H
#define CONCUBREAD_COCINERO_H

#include <string>
#include <memory>
#include "Actor.h"
#include "../../fifos/FifoLectura.h"

class Cocinero : public Actor {
public:
    explicit Cocinero();

    void ejercer_tarea();

    void recibir_pedido(bool *seguir_recibiendo_pedidos);

    void realizar_pedido();

    void entregar_pedido_a_repartidor();

protected:
    std::string id;
    struct flock fl;
    std::string id_pedido_actual;

    std::unique_ptr<FifoLectura> canal_recepcionista;
    char buffer[FIFO_PEDIDOS_BUFFSIZE];
};

#endif //CONCUBREAD_COCINERO_H
