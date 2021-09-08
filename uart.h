#ifndef UART_H
#define UART_H

#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include "util/delay.h"


void USART_init( unsigned int ubrr);
int USART_transmit( unsigned char  data, FILE* file);
int USART_receive(FILE* file);

#endif