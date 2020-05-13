//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_RECEPCIONISTA_H
#define CONCUBREAD_RECEPCIONISTA_H

#include "Actor.h"

class Recepcionista : public Actor {
public:
    explicit Recepcionista(int id);
    void ejercer_tarea() override;

private:
    void pedir_pan();
    void pedir_pizza();
    int id;

    void hacer_pedidos();
};


#endif //CONCUBREAD_RECEPCIONISTA_H
