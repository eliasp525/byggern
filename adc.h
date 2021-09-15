#ifndef ADC_H
#define ADC_H

#define SINGLE_CHANNEL_ADDRESS 0b10000000
#define Y_DIRECTION 0
#define X_DIRECTION 1

#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include "external_memory.h"
#include <avr/io.h>

uint8_t read_adc_channel(uint8_t channel_number); 


#endif