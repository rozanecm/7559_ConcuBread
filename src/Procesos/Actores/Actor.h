//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_ACTOR_H
#define CONCUBREAD_ACTOR_H


#include "../../fifos/FifoEscritura.h"
#include "../../utils/consts.h"
#include "../Proceso.h"

class Actor : public Proceso {
public:
    Actor();
    ~Actor();
    void mandar_msj_fifo(std::string mensaje, FifoEscritura *fifo);
    void mandar_msj_debug(std::string mensaje);

protected:
    FifoEscritura canal_debug = FifoEscritura(ARCHIVO_FIFO_DEBUG);
};


#endif //CONCUBREAD_ACTOR_H
