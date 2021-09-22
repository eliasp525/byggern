#ifndef OLED_H
#define OLED_H

#include "external_memory.h"
#include "input.h"

void oled_init();

void write_c(uint8_t byte);

void oled_goto_column(uint8_t column);

void oled_home();

void oled_reset();

void oled_clear_page(unsigned int page);

uint8_t menu_loop(string *menu_elements, int *position);

void menu_init(string *menu_elements, int *position);
#endif   