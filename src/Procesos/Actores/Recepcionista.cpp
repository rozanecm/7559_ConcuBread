//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include "Recepcionista.h"

#define CANT_PIZZAS 2
#define CANT_PANES 1

Recepcionista::Recepcionista(int id) : id(id){
    canal_pizzeros.abrir();
    canal_panaderos.abrir();
}

Recepcionista::~Recepcionista() {
    canal_pizzeros.cerrar();
    canal_panaderos.cerrar();
}

void Recepcionista::ejercer_tarea() {
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
//    TODO refactor meter el cpo del metodo que llamo aca directamente
    hacer_pedido_pizzeros();
}

void Recepcionista::pedir_pan() {
//    TODO sacar pasamanos.
    hacer_pedido_panaderos();
}

void Recepcionista::hacer_pedido_pizzeros() {
    auto id_pizza = id_prox_pizza();
    mandar_msj_debug("Recepc. " + std::to_string(id) + " Encargando pizza " + id_pizza);
    mandar_msj_fifo(id_pizza, &canal_pizzeros);
    cantidad_pizzas_encargadas++;
}

void Recepcionista::hacer_pedido_panaderos() {
    auto id_pan = id_prox_pan();
    mandar_msj_debug("Recepc. " + std::to_string(id) + " Encargando pan " + id_pan);
    mandar_msj_fifo(id_pan, &canal_panaderos);
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
