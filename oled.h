#ifndef OLED_H
#define OLED_H

#include "external_memory.h"

void oled_init();

void write_c(uint8_t byte);

void oled_reset();

void oled_clear_page(unsigned int page);

#endif