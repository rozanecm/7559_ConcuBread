//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_PIZZERO_H
#define CONCUBREAD_PIZZERO_H


#include "Cocinero.h"
#include "../../fifos/FifoLectura.h"

class Pizzero : public Cocinero {
public:
    explicit Pizzero(int id_pizzero);
    ~Pizzero();

    void set_id(int id_pizzero);
};


#endif //CONCUBREAD_PIZZERO_H
