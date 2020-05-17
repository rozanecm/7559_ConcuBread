//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Recepcionista.h"

#define CANT_PIZZAS 3
#define CANT_PANES 2

Recepcionista::Recepcionista(int id) : id(id){
    canal_pizzeros.abrir();
    canal_panaderos.abrir();
}

Recepcionista::~Recepcionista() {
    std::cout << "destruyendo recep." << std::endl;
    canal_panaderos.cerrar();
    canal_pizzeros.cerrar();
}

void Recepcionista::ejercer_tarea() {
    std::cout << "Recepc. con nro de serie " << id << " ejerciendo tarea" << std::endl;
    hacer_pedidos();
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

void Recepcionista::pedir_pizza() {
    mandar_msj_debug("Recepc. Encargando pizza");
    hacer_pedido_pizzeros();
}

void Recepcionista::pedir_pan() {
    mandar_msj_debug("Recepc. Encargando pan");
    hacer_pedido_panaderos();
}

void Recepcionista::hacer_pedido_pizzeros() {
    mandar_msj_fifo(id_prox_pizza(), &canal_pizzeros);
    cantidad_pizzas_encargadas++;
}

void Recepcionista::hacer_pedido_panaderos() {
    mandar_msj_fifo(id_prox_pan(), &canal_panaderos);
    cantidad_panes_encargados++;
}

std::string Recepcionista::id_prox_pizza() const {
    std::string id_pedido = "Piz";
    if(this->id < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(this->id);
    if(this->cantidad_pizzas_encargadas < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(cantidad_pizzas_encargadas);
    return id_pedido;
}

std::string Recepcionista::id_prox_pan() const {
    std::string id_pedido = "Pan";
    if(this->id < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(this->id);
    if(this->cantidad_panes_encargados < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(cantidad_panes_encargados);
    return id_pedido;
}
