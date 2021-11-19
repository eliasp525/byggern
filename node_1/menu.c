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

char high1[17];
char high2[17];
char high3[17];

char * high_score[TOTAL_PAGES] = {
    high1,
    high2,
    high3,
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
};


void init_highscore(){
    uint8_t high_score1 = 2;
    uint8_t high_score2 = 1;
    uint8_t high_score3 = 3;

    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS1, high_score1);
    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS2, high_score2);
    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS3, high_score3);
}



MenuType high_score_menu = {.elements = high_score, .min = 3, .max = 3};
MenuType main_menu = {.elements = main_menu_elem, .min = 0, .max = 3};
MenuType player_menu = {.elements = players, .min = 0, .max = 2};

GameState menu(int8_t* bias, uint8_t* player){
    
    

    uint8_t state = 3;
        while(1){
        switch (state){
            case 0:
                player = run_menu(bias, player_menu);
                return PLAY_TIMED;
                break;
            case 1:
                return PLAY_FREE;
                break;
            case 2:
                make_highscore_menu();
                state = run_menu(bias, high_score_menu);
                break;    
            case 3:
                state = run_menu(bias, main_menu);
                if (state == 3){
                    return EXIT;
                }
                break;
        }
    }
}

uint8_t run_menu(int8_t* bias, MenuType menu){
    uint8_t current_option = menu.min;
    oled_reset(); 
    refresh_menu((*menu.elements), current_option);
    INPUT input = NEUTRAL;

    //printf("bias0: %d\r\n", bias[0]);
    while(1){
        input = read_input(bias, input);
        printf("Input menu: %d\r\n", input);
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
            return current_option;
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


void make_highscore_menu(){
    

    uint8_t val1 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS1);
    uint8_t val2 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS2);
    uint8_t val3 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS3);
    
    snprintf(high1, 17, "OLV: %d",val1);
    snprintf(high2, 16, "ADR: %d",val2);
    snprintf(high3, 16, "ELI: %d",val3);
}

void update_high_score(uint8_t player, uint8_t score){
    if (player > 2 || player < 0){
        printf("playervalue outside range, val: %d \r\n", player);
        return;
    }
    uint8_t high_score = eeprom_read_byte((uint8_t*)(HIGHSCORE_BASEADRESS + player));
    if (score > high_score){
        eeprom_write_byte((uint8_t*)(HIGHSCORE_BASEADRESS + player), score);
    }
   
}


void update_score_screen(uint8_t score){
    oled_reset();
    oled_goto_position(32,1);
    char str[] = "Score: ";
    char scorestr[5];
    sprintf(scorestr, "%d", score);
    strcat(str, scorestr);
    printo(str, 0);
}


