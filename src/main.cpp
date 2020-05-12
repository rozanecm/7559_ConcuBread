#include <iostream>
#include <unistd.h>
#include "ProcessManager.h"
#include "enums.h"
#include "DebugPrint.h"
#include "fifos/FifoLectura.h"
#include "fifos/FifoEscritura.h"
#include "signals/SIGINT_Handler.h"
#include "signals/SignalHandler.h"

#define PANADEROS 5
#define PIZZEROS 1
#define RECEPCIONISTAS 1

#define BUFFSIZE 100
#define ARCHIVO_FIFO "/tmp/archivo_fifo"

int main() {
    std::cout << "Bienvenido a ConcuBread!" << std::endl;
    std::cout << "Pid padre: " << getpid() << std::endl;
    switch (ProcessManager::crear_procesos(PANADEROS, PIZZEROS, RECEPCIONISTAS)) {
        case Padre: {
            std::cout << "soy padre con pid: " << getpid() << std::endl;
            // event handler para la senial SIGINT (-2)
            SIGINT_Handler sigint_handler;

            // se registra el event handler declarado antes
            SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

            FifoLectura canal ( ARCHIVO_FIFO );
            char buffer[BUFFSIZE];
            canal.abrir();

            // mientras no se reciba la senial SIGINT, el proceso realiza su trabajo
            ssize_t bytesLeidos = 1;

            while (sigint_handler.getGracefulQuit() == 0
//            and bytesLeidos > 0
            ) {
                bytesLeidos = canal.leer(static_cast<void *>(buffer), BUFFSIZE);
                if (bytesLeidos > 0){
                    std::string mensaje = buffer;
                    mensaje.resize(bytesLeidos);
                    std::cout << "cant bytes leidos" << bytesLeidos << std::endl;
                    std::cout << "[Lector] Lei el dato del fifo: " << mensaje << std::endl;
                }
            }
            // se recibio la senial SIGINT, el proceso termina
            SignalHandler :: destruir ();

            canal.cerrar();
            std::cout << "soy padre y estoy saliendo. Salu3!" << std::endl;
            break;
        }
        case MtroPanadero: {
            FifoEscritura canal(ARCHIVO_FIFO);
            std::string mensaje = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the.";

            canal.abrir();
//            sleep(5);
            canal.escribir(static_cast<const void *>(mensaje.c_str()), mensaje.length());
            std::cout << "[Escritor] Escribi el mensaje " << mensaje << " en el fifo" << std::endl;

            std::cout << "soy un panadero" << std::endl;
            break;
        }
        case MtroPizzero:
            std::cout << "soy un pizzero" << std::endl;
            break;
        case Recepcionista:
            std::cout << "soy un recepcionista" << std::endl;
            break;
        case EspecialistaMasaMadre:
            std::cout << "soy el especialista MM" << std::endl;
            break;
    }
    return 0;
}
