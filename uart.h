#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>

#include "constants.h"

void USART_init(unsigned int ubrr);
int USART_transmit(unsigned char data);
int USART_receive();

#endif