//
// Created by rozanecm on 5/13/20.
//

#ifndef CONCUBREAD_PROCESO_H
#define CONCUBREAD_PROCESO_H


#include "../signals/SIGINT_Handler.h"

class Proceso {
public:
    virtual ~Proceso(){};
    virtual void ejercer_tarea() = 0;

protected:
    SIGINT_Handler sigint_handler;
};


#endif //CONCUBREAD_PROCESO_H
