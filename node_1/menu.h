#ifndef MENU_H
#define MENU_H

#include <avr/eeprom.h>
#include <string.h>
#include "oled.h"
#include "input.h"

#define HIGHSCORE_BASEADRESS 0
#define HIGHSCORE_ADDRESS1 0
#define HIGHSCORE_ADDRESS2 1
#define HIGHSCORE_ADDRESS3 2

typedef struct{
    const char *elements[TOTAL_PAGES];
    uint8_t min;
    uint8_t max;
} MenuType;

typedef enum {MENU, PLAY_TIMED, PLAY_FREE, EXIT}GameState;

GameState menu(int8_t* bias, uint8_t* player);

uint8_t run_menu(int8_t* bias, MenuType menu);

void refresh_menu(char* menu_elements[], uint8_t current_option);

void player_select(uint8_t current_option);

void make_highscore_menu();

void update_high_score(uint8_t player, uint8_t score);

void update_score_screen(uint8_t score);


#endif