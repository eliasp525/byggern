#ifndef SPI_H
#define SPI_H

#include "constants.h"
#include "bit_operations.h"
#include <util/delay.h>
#include <avr/io.h>

void spi_master_init();

char spi_master_transceive(char cData);

void end_transmission();

void start_transmission();



#endif