//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Recepcionista.h"

#define CANT_PIZZAS 3
#define CANT_PANES 2

void Recepcionista::pedir_pan() {
    mandar_msj_debug("Recepc. Encargando pan");
}

void Recepcionista::pedir_pizza() {
    mandar_msj_debug("Recepc. Encargando pizza");
}

void Recepcionista::hacer_pedidos() {
    for (int i = 0; i < CANT_PIZZAS; ++i){
        pedir_pizza();
        sleep(2);
    }
    for (int i = 0; i < CANT_PANES; ++i){
        pedir_pan();
        sleep(2);
    }
}

Recepcionista::Recepcionista(int id) : id(id){

}

void Recepcionista::ejercer_tarea() {
    std::cout << "Recepc. con nro de serie " << id << " ejerciendo tarea" << std::endl;
    hacer_pedidos();
}