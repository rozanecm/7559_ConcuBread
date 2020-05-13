//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_PADRE_H
#define CONCUBREAD_PADRE_H


#include "../signals/SIGINT_Handler.h"
#include "../fifos/FifoLectura.h"
#include "../utils/fifo_consts.h"
#include "../utils/DebugPrint.h"
#include "Proceso.h"

class Padre : public Proceso {
public:
    Padre();
    ~Padre();

    void ejercer_tarea() override;

private:
    DebugPrint debug_printer;
    SIGINT_Handler sigint_handler;
    FifoLectura canal = FifoLectura(ARCHIVO_FIFO);
    char buffer[FIFO_BUFFSIZE];

    void atender_hijos();
};


#endif //CONCUBREAD_PADRE_H
