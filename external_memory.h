#ifndef EXTERNAL_MEMORY_H
#define EXTERNAL_MEMORY_H

#include <stdint.h>

#define EXTERNAL_MEMORY_LOCATION 0x1000

#define EXTERNAL_MEMORY ((EXTERNAL_MEMORY_MAP*) EXTERNAL_MEMORY_LOCATION )

typedef struct
{
    volatile uint8_t OLED_COMMAND[512];
    volatile uint8_t OLED_DATA[512];
    volatile uint8_t ADC[1024];
    volatile uint8_t SRAM[2048];
} EXTERNAL_MEMORY_MAP;

void config_external_memory();

#endif