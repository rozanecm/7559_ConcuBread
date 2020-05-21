//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_DEBUGPRINTER_H
#define CONCUBREAD_DEBUGPRINTER_H


#include <fstream>
#include "../signals/SIGINT_Handler.h"
#include "../fifos/FifoLectura.h"
#include "../utils/consts.h"
#include "Proceso.h"

class DebugPrinter : public Proceso {
public:
    DebugPrinter();
    ~DebugPrinter();

    void ejercer_tarea() override;

private:
    FifoLectura canal_debug = FifoLectura(ARCHIVO_FIFO_DEBUG);
    char buffer[FIFO_DEBUG_BUFFSIZE];
    void atender_debug_msgs();

    void print(const std::string&);

    std::ofstream debug_file;
};


#endif //CONCUBREAD_DEBUGPRINTER_H
