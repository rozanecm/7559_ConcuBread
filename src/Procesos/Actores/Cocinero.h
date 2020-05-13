//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_COCINERO_H
#define CONCUBREAD_COCINERO_H

#include <string>
#include "Actor.h"

class Cocinero : public Actor {
public:
    explicit Cocinero(int id_cocinero);
    void recibir_pedido();
    void realizar_pedido();
    void entregar_pedido_a_repartidor();

private:
    //    FifoEscritura canal = FifoEscritura(ARCHIVO_FIFO);
    int catidad_de_pedidos_en_cola;
protected:
    int id;
};

#endif //CONCUBREAD_COCINERO_H
