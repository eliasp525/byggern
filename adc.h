#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <util/delay.h>

#include "constants.h"
#include "external_memory.h"

uint8_t read_adc_channel(uint8_t channel_number);

#endif