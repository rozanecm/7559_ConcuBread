//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Panadero.h"

Panadero::Panadero(int id_panadero) : Cocinero(id_panadero){

}

void Panadero::ejercer_tarea() {
    std::cout << "Panadero con nro de serie " << id << " ejerciendo tarea" << std::endl;
}
