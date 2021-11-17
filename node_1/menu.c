#include "menu.h"



const char * main_menu_elem[TOTAL_PAGES] = {
    "Play Game",
    "Free Play",
    "High Score",
    "Exit",
    "",
    "",
    "",
    "===MAIN MENU===="
};

char * const high_score[TOTAL_PAGES] = {
    "OLV: 0",
    "ADR: 0",
    "ELI: 0",
    "Back",
    "",
    "",
    "",
    "===HIGH SCORE==="
};

const char * players[TOTAL_PAGES] = {
    "OLVE",
    "ADRIAN",
    "ELIAS",
    "",
    "",
    "",
    "",
    "==PLAYER SELECT="
}

const uint8_t high_scores[] EEMEM = {0, 0, 0};

MenuType high_score_menu = {.elements = high_score, .min = 3, .max = 3};
MenuType main_menu = {.elements = main_menu_elem, .min = 0, .max = 3};
MenuType player_menu = {.elements = players, .min = 0, .max = 2}

GameState run_menu(int8_t* bias, MenuType menu){
    uint8_t current_option = menu.min;
    oled_reset(); //put reset here instead of in refresh_menu()
    refresh_menu((*menu.elements), current_option);
    INPUT input = NEUTRAL;

    //printf("bias0: %d\r\n", bias[0]);
    while(1){
        input = read_input(bias, input);
        //printf("Input menu: %d\r\n", input);
        switch (input)
        {        
        case UP:
            if (current_option != menu.min){
                current_option--;
            }
            
            break;
        case DOWN:
            if (current_option != menu.max){
                current_option++;
            }
            break;
        case ANALOG_PRESS:
            switch (current_option){
                case 0:
                    oled_draw_star();
                    return PLAY_TIMED;

                case 1:
                    oled_draw_star();
                    return PLAY_FREE;

                case 2:
                    oled_draw_star();
                    _delay_ms(1000);
                    run_menu(&bias, high_score_menu);
                    break;

                case 3:
                    return EXIT;


                
            }
            break;
        default:
            break;
        }
        refresh_menu((*menu.elements), current_option);
        _delay_ms(100);
    }

}

void refresh_menu(char* menu_elements[], uint8_t current_option){
    //oled_reset(); dont need to reset the screen when we are overwriting all pages anyways?
    for (uint8_t i = 0; i < TOTAL_PAGES; i++){
        oled_goto_position(0, i);
        uint8_t invert = 0;
        if (current_option == i){
            invert = 1;
        }
        printo(menu_elements[i], invert);
    }
}

void player_select(){
    refresh_menu((*player_menu.elements), current_option);
}


void make_highscore_menu(){
    
    char places[3][5];
    sprintf(places[0], "%d", eeprom_read_byte(&(high_scores[0])););
    sprintf(places[1], "%d", eeprom_read_byte(&(high_scores[1])););
    sprintf(places[2], "%d", eeprom_read_byte(&(high_scores[2])););
    char * high_score_place[3] = {"OLV: ", "ADR: ", "ELI: "};
    strcat(high_score_place[0],places[0]);
    strcat(high_score_place[1],places[1]);
    strcat(high_score_place[2],places[2]);

    high_score_menu.elements[0] = high_score_place[0];
    high_score_menu.elements[1] = high_score_place[1];
    high_score_menu.elements[2] = high_score_place[2];
}

void update_high_score(uint8_t player, uint8_t score){
    eeprom_write_byte(&(high_scores[player]), score)
}


void update_score_screen(uint8_t score){
    oled_goto_position(24,1);
    char* str[] = "Score: ";
    char scorestr[3];
    sprintf(scorestr, "%d", score);
    strcat(str, scorestr);
    printo(str, 0);
}


