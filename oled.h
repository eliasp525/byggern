#ifndef OLED_H
#define OLED_H

#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "constants.h"
#include "external_memory.h"
#include "fonts.h"
#include "input.h"

void oled_init();

void write_d(uint8_t data);

void write_c(uint8_t byte);

// void oled_goto_column(uint8_t column);

// void oled_goto_page(uint8_t page);

void oled_home();

void oled_reset();

void oled_clear_page(uint8_t page);

void printo(char* string, uint8_t invert);

void oled_goto_position(uint8_t column, uint8_t page);

void run_menu(int* bias, char* menu_elements[]);

// uint8_t menu_loop(char *menu_elements, int *position);

// void menu_init(char *menu_elements, int *position);
#endif