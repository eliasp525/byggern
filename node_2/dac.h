
#ifndef DAC_H
#define DAC_H

#include "stdint.h"
#include "sam.h"

#define DAC_RESOLUTION 4096

//uint32_t current_cdr_value;

void dac_init();

void dac_convert(uint32_t value);

#endif