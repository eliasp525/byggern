
#ifndef ADC_H
#define ADC_H

#include "sam.h"

#define ADC_MR_LOWRES (0x1u << 4)

void adc_init();

void adc_read();

volatile uint32_t analog_value;


#endif