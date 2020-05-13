//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_ACTOR_H
#define CONCUBREAD_ACTOR_H


#include "../../fifos/FifoEscritura.h"
#include "../../utils/fifo_consts.h"

class Actor {
public:
    Actor();
    ~Actor();
    void mandar_msj_debug(std::string mensaje);

private:
    FifoEscritura canal = FifoEscritura(ARCHIVO_FIFO);
};


#endif //CONCUBREAD_ACTOR_H
