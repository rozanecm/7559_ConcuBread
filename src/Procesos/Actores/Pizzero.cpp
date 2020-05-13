//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Pizzero.h"

Pizzero::Pizzero(int id_pizzero) : Cocinero(id_pizzero) {

}

void Pizzero::ejercer_tarea() {
    std::cout << "Pizzero con nro de serie " << id << " ejerciendo tarea" << std::endl;
}
