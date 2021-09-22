#ifndef OLED_H
#define OLED_H

#include "fonts.h"
#include "external_memory.h"

void oled_init();

void write_c(uint8_t byte);

void oled_goto_column(uint8_t column);

void oled_home();

void oled_reset();

void oled_clear_page(unsigned int page);

#endif