//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_PANADERO_H
#define CONCUBREAD_PANADERO_H


#include "Cocinero.h"
#include "../../fifos/FifoLectura.h"

class Panadero : public Cocinero {
public:
    explicit Panadero(int id_panadero);

    ~Panadero();

    void set_id(int id_panadero);
};


#endif //CONCUBREAD_PANADERO_H
