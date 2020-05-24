//
// Created by rozanecm on 5/12/20.
//

#include <iostream>
#include <random>
#include "Recepcionista.h"

#define CANT_PIZZAS 2
#define CANT_PANES 1

Recepcionista::Recepcionista(int id) : id(id) {
    canal_pizzeros.abrir();
    canal_panaderos.abrir();
}

Recepcionista::~Recepcionista() {
    canal_pizzeros.cerrar();
    canal_panaderos.cerrar();
    canal_pizzeros.eliminar();
    canal_panaderos.eliminar();
}

void Recepcionista::ejercer_tarea() {
    hacer_pedidos();
}

void Recepcionista::hacer_pedidos() {
    /* La parte random esta sacada de
     * https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
     * */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    auto cant_pizzas_a_encargar = dis(gen);
    auto cant_panes_a_encargar = dis(gen);

    auto decision_pizza_o_pan = dis(gen);

    int pizzas_encargadas = 0;
    int panes_encargados = 0;
    while (pizzas_encargadas < cant_pizzas_a_encargar or panes_encargados <
                                                         cant_panes_a_encargar){
        if (decision_pizza_o_pan % 2 == 0 and pizzas_encargadas <
                                              cant_pizzas_a_encargar) {
            pizzas_encargadas++;
            pedir_pizza(pizzas_encargadas, cant_pizzas_a_encargar);
            sleep(dis(gen));
        } else if (panes_encargados < cant_panes_a_encargar) {
            panes_encargados++;
            pedir_pan(panes_encargados, cant_panes_a_encargar);
            sleep(dis(gen));
        }
        decision_pizza_o_pan = dis(gen);
    }
}

void Recepcionista::pedir_pizza(int numero_de_encargo_pizza,
                                int cant_total_de_pizzas_a_hacer) {
    hacer_pedido_pizzeros(numero_de_encargo_pizza,
                          cant_total_de_pizzas_a_hacer);
}

void Recepcionista::pedir_pan(int numero_de_encargo_pan,
                              int cant_total_de_panes_a_hacer) {
    hacer_pedido_panaderos(numero_de_encargo_pan, cant_total_de_panes_a_hacer);
}

void Recepcionista::hacer_pedido_pizzeros(int numero_de_encargo_pizza,
                                          int cant_total_de_pizzas_a_hacer) {
    auto id_pizza = id_prox_pizza();

    mandar_msj_debug("Recepc. " + std::to_string(id) +
                     " Encargando pizza " + id_pizza + " (" +
                     std::to_string(numero_de_encargo_pizza) + "/" +
                     std::to_string(cant_total_de_pizzas_a_hacer) + ")");

    mandar_msj_fifo(id_pizza, &canal_pizzeros);
    cantidad_pizzas_encargadas++;
}

void Recepcionista::hacer_pedido_panaderos(int numero_de_encargo_pan,
                                           int cant_total_de_panes_a_hacer) {
    auto id_pan = id_prox_pan();

    mandar_msj_debug("Recepc. " + std::to_string(id) +
                     " Encargando pan " + id_pan + " (" +
                     std::to_string(numero_de_encargo_pan) + "/" +
                     std::to_string(cant_total_de_panes_a_hacer) + ")");

    mandar_msj_fifo(id_pan, &canal_panaderos);
    cantidad_panes_encargados++;
}

std::string Recepcionista::id_prox_pizza() const {
    std::string id_pedido = "Piz";
    if (this->id < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(this->id);
    if (this->cantidad_pizzas_encargadas < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(cantidad_pizzas_encargadas);
    return id_pedido;
}

std::string Recepcionista::id_prox_pan() const {
    std::string id_pedido = "Pan";
    if (this->id < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(this->id);
    if (this->cantidad_panes_encargados < 10) {
        id_pedido += "0";
    }
    id_pedido += std::to_string(cantidad_panes_encargados);
    return id_pedido;
}
