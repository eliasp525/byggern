#ifndef ADC_H
#define ADC_H

#define SINGLE_CHANNEL_ADDRESS 0b10000000

#include <util/delay.h>
#include "external_memory.h"
#include <avr/io.h>

void read_adc();


#endif