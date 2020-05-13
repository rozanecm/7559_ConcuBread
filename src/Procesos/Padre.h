//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_PADRE_H
#define CONCUBREAD_PADRE_H


#include "../signals/SIGINT_Handler.h"
#include "../fifos/FifoLectura.h"
#include "../utils/fifo_consts.h"
#include "../utils/DebugPrint.h"

class Padre {
public:
    Padre();
    ~Padre();

    void atender_hijos(DebugPrint *pPrint);

private:
    SIGINT_Handler sigint_handler;
    FifoLectura canal = FifoLectura(ARCHIVO_FIFO);
    char buffer[FIFO_BUFFSIZE];
};


#endif //CONCUBREAD_PADRE_H
