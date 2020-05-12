//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_RECEPCIONISTA_H
#define CONCUBREAD_RECEPCIONISTA_H


//#include "../fifos/FifoEscritura.h"
//#include "../utils/fifo_consts.h"
#include "Actor.h"

class Recepcionista : public Actor {
public:
//    Recepcionista();
//    ~Recepcionista();

    void pedir_pan();
    void pedir_pizza();

private:
//    FifoEscritura canal = FifoEscritura(ARCHIVO_FIFO);
};


#endif //CONCUBREAD_RECEPCIONISTA_H
