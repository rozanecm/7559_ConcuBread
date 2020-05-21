//
// Created by rozanecm on 5/21/20.
//

#ifndef CONCUBREAD_PADRE_H
#define CONCUBREAD_PADRE_H


#include "Actores/Actor.h"

class Padre : public Proceso {
    void ejercer_tarea() override;

private:
    FifoEscritura canal_debug = FifoEscritura(ARCHIVO_FIFO_DEBUG);

    void reportarse();
};


#endif //CONCUBREAD_PADRE_H
