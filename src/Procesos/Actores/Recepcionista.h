//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_RECEPCIONISTA_H
#define CONCUBREAD_RECEPCIONISTA_H

#include "Actor.h"

class Recepcionista : public Actor {
public:
    explicit Recepcionista(int id);
    ~Recepcionista();
    void ejercer_tarea() override;

private:
    void pedir_pan(int numero_de_encargo_pan, int cant_total_de_panes_a_hacer);
    void pedir_pizza(int numero_de_encargo_pizza, int cant_total_de_pizzas_a_hacer);
    int id;

    void hacer_pedidos();
    int cantidad_pizzas_encargadas = 0;
    int cantidad_panes_encargados = 0;

    FifoEscritura canal_panaderos = FifoEscritura(ARCHIVO_FIFO_PANADEROS);
    FifoEscritura canal_pizzeros = FifoEscritura(ARCHIVO_FIFO_PIZZEROS);

    void hacer_pedido_panaderos(int numero_de_encargo_pan, int cant_total_de_panes_a_hacer);
    void hacer_pedido_pizzeros(int numero_de_encargo_pizza, int cant_total_de_pizzas_a_hacer);

    std::string id_prox_pizza() const;

    std::string id_prox_pan() const;
};


#endif //CONCUBREAD_RECEPCIONISTA_H
