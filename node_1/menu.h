#ifndef MENU_H
#define MENU_H

#include <avr/eeprom.h>
#include "oled.h"
#include "input.h"

GameState run_menu(int8_t* bias, MenuType menu);

void refresh_menu(char* menu_elements[], uint8_t current_option);

void player_select(uint8_t current_option);

void make_highscore_menu();

void update_high_score(uint8_t player, uint8_t score);

void update_score_screen(uint8_t score);


#endif