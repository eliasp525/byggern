#ifndef OLED_H
#define OLED_H

#include "external_memory.h"

void oled_init();

void write_d(uint8_t address, uint8_t data);

void write_c(uint8_t byte);

void oled_goto_column(uint8_t column);

void oled_goto_page(uint8_t page);

void oled_home();

void oled_reset();

void oled_clear_page(uint8_t page);

#endif