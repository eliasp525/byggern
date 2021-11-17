#ifndef OLED_H
#define OLED_H

#include <stdio.h>
#include <avr/pgmspace.h>

#include "constants.h"
#include "external_memory.h"
#include "fonts.h"
#include "input.h"

#include <util/delay.h> //constants.h must be included before util/delay.h

typedef struct{
    const char *elements[TOTAL_PAGES];
    uint8_t min;
    uint8_t max;
} MenuType;

typedef enum {PLAY_TIMED, PLAY_FREE, EXIT}GameState;

MenuType main_menu;

MenuType high_score_menu;

void oled_init();

void write_d(uint8_t data);

void write_c(uint8_t byte);

// void oled_goto_column(uint8_t column);

// void oled_goto_page(uint8_t page);

void oled_home();

void oled_reset();

void oled_clear_page(uint8_t page);

void printo(char* string, uint8_t invert);

void oled_draw_star();

void oled_goto_position(uint8_t column, uint8_t page);

GameState run_menu(int8_t* bias, MenuType menu);

// uint8_t menu_loop(char *menu_elements, int *position);

// void menu_init(char *menu_elements, int *position);
#endif