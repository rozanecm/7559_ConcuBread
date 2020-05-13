//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_PIZZERO_H
#define CONCUBREAD_PIZZERO_H


#include "Cocinero.h"

class Pizzero : public Cocinero {
public:
    explicit Pizzero(int id_pizzero);
    void ejercer_tarea() override;

};


#endif //CONCUBREAD_PIZZERO_H
