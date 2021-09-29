#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#include "constants.h"
#include "external_memory.h"

#include <util/delay.h> //constants.h must be included before util/delay.h

uint8_t read_adc_channel(uint8_t channel_number);

#endif