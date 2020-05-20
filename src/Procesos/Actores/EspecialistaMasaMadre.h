//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_ESPECIALISTAMASAMADRE_H
#define CONCUBREAD_ESPECIALISTAMASAMADRE_H


#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include "Actor.h"
#include "../../fifos/FifoLectura.h"

class EspecialistaMasaMadre : public Actor{
public:
    EspecialistaMasaMadre();
    ~EspecialistaMasaMadre();
    void ejercer_tarea() override;

private:
    FifoLectura canal_cocineros = FifoLectura(ARCHIVO_FIFO_PEDIDOS_MM);
    char buffer[FIFO_ESPECIALISTA_MM_BUFFSIZE];

    std::string escuchar_pedidos(bool *seguir_recibiendo_pedidos);

    void entregar_pedido(const std::string& id_solicitante);

    bool existe_canal_envio_mm(const std::string &id_pedido);

    void cerrar_canales_particulares();

    FifoEscritura * obtener_canal_envio_mm(const std::string &id_solicitante);

    std::vector<std::pair<std::string, FifoEscritura*>> canales_envio_mm;
};


#endif //CONCUBREAD_ESPECIALISTAMASAMADRE_H
