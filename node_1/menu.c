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

char * high_score[TOTAL_PAGES] = {
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
};


void init_highscore(){
    uint8_t high_score1 = 2;
    uint8_t high_score2 = 1;
    uint8_t high_score3 = 2;

    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS1, high_score1);
    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS2, high_score1);
    eeprom_update_byte((uint8_t*)HIGHSCORE_ADDRESS3, high_score1);
}



MenuType high_score_menu = {.elements = high_score, .min = 3, .max = 3};
MenuType main_menu = {.elements = main_menu_elem, .min = 0, .max = 3};
MenuType player_menu = {.elements = players, .min = 0, .max = 2};

GameState menu(int8_t* bias, uint8_t* player){
    
    //make_highscore_menu();

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
    
    //char places[3][5];
    //free(high_score_menu.elements[0]);
    //free(high_score_menu.elements[1]);
    //free(high_score_menu.elements[2]);

    uint8_t val1 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS1);
    uint8_t val2 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS2);
    uint8_t val3 = eeprom_read_byte((uint8_t*) HIGHSCORE_ADDRESS3);
    //sprintf(places[0], "%d", byte);
    //printf("place: %s \r\n", places);
    //sprintf(places[1], "%d", eeprom_read_byte(&(high_scores[1])));
    //sprintf(places[2], "%d", eeprom_read_byte(&(high_scores[2])));
    //char * high_score_place[3] = {"OLV: ", "ADR: ", "ELI: "};
    
    // char* str1;
    // char* str2;
    // char* str3;
    // str1 = (char*)malloc(17*sizeof(char));
    // str1 = (char*)malloc(17*sizeof(char));
    // str1 = (char*)malloc(17*sizeof(char));
    
    snprintf(make_highscore_menu.elements[0], 16, "OLV: %d",val1);
    snprintf(make_highscore_menu.elements[1], 16, "ADR: %d",val2);
    snprintf(make_highscore_menu.elements[2], 16, "ELI: %d",val3);
    //strcat(high_score_place,places);
    //strcat(high_score_place[1],places[1]);
    //strcat(high_score_place[2],places[2]);
    //printf("high_score_place: %s \r\n", high_score_place);
    //strcpy((*high_score_menu.elements[0]), high_score_place);
    //snprintf(high_score_menu.elements[0], 16, "%s", high_score_place);
    //high_score_menu.elements[0][16] = '\0';
    //high_score_menu.elements[0] = high_score_place;
    //high_score_menu.elements[1] = high_score_place[1];
    //high_score_menu.elements[2] = high_score_place[2];
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


