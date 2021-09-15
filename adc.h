#ifndef ADC_H
#define ADC_H

#define SINGLE_CHANNEL_ADDRESS 0b10000000

#include <util/delay.h>
#include "external_memory.h"
#include <avr/io.h>

uint8_t read_adc_channel(uint8_t channel_number);


#endif