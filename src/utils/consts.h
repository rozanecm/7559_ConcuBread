//
// Created by rozanecm on 5/12/20.
//

#ifndef CONCUBREAD_CONSTS_H
#define CONCUBREAD_CONSTS_H

#define FIFO_DEBUG_BUFFSIZE 100

/* el id que se manda con el pedido tiene siempre esta longitud */
#define FIFO_PEDIDOS_BUFFSIZE 7
/* el msj que le mandan es el id, que tiene 5 chars siempre (Piz/Pan + id de dos digitos) */
#define FIFO_ESPECIALISTA_MM_BUFFSIZE 5

/* Se definen las siguientes ctes. para entender mas facilmente los valores en el codigo */
#define MENSAJE_PARA_ENVIAR_MM_A_COCINEROS "X"
#define LENGTH_MSJ_ENVIO_MM 1

#define ARCHIVO_FIFO_DEBUG "/tmp/archivo_debug"
#define ARCHIVO_FIFO_PANADEROS "/tmp/archivo_fifo_panaderos"
#define ARCHIVO_FIFO_PIZZEROS "/tmp/archivo_fifo_pizzeros"
#define ARCHIVO_FIFO_PEDIDOS_MM "/tmp/archivo_fifo_pedidos_MM"


#endif //CONCUBREAD_CONSTS_H
