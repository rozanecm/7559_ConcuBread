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

    ~Cocinero();

    void ejercer_tarea();

    void recibir_pedido(bool *seguir_recibiendo_pedidos);

    void realizar_pedido();

    void entregar_pedido_a_repartidor();

    void pedir_racion_mm();

protected:
    std::string id;
    struct flock fl;
    std::string id_pedido_actual;

    std::unique_ptr<FifoLectura> canal_recepcionista;
    char buffer_recepcionista[FIFO_PEDIDOS_BUFFSIZE];

private:
    FifoEscritura canal_envio_pedidos_especialista_MM =
            FifoEscritura(ARCHIVO_FIFO_PEDIDOS_MM);

    std::unique_ptr<FifoLectura> canal_recepcion_de_mm;
    char buffer_recepcion_mm[LENGTH_MSJ_ENVIO_MM];

    void esperar_envio_mm();

    void abrir_canal_recepcion_de_mm();

    bool canal_recepcion_de_mm_fue_abierto = false;
};

#endif //CONCUBREAD_COCINERO_H
