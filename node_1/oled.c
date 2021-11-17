#include "oled.h"



void write_d(uint8_t data) { EXTERNAL_MEMORY->OLED_DATA[0] = data; }

void write_c(uint8_t byte) { EXTERNAL_MEMORY->OLED_COMMAND[0] = byte; }

void oled_goto_column(uint8_t column) {
    if (column >= OLED_WIDTH) {
        printf('\n\rERROR: column out of range. oled_goto_page tried to access column %d', column);
        printf('column reset to 0\r\n');
        column = 0;
    }
    uint8_t lower_nibble = column & 0xf ;
    uint8_t upper_nibble = (column >> 4) | 0x10;

    write_c(lower_nibble);
    write_c(upper_nibble);
}

void oled_home() {
    oled_goto_page(0);
    oled_goto_column(0);
}

void oled_reset() {
    for (unsigned int j = 0; j < TOTAL_PAGES; j++) {
        oled_clear_page(j);
    }
}

void oled_clear_page(uint8_t page) {
    oled_goto_page(page);
    for (int i = 0; i < OLED_WIDTH; i++) {
        write_d(0x00);
    }
}

void oled_print(char letter, uint8_t invert) {
    if (letter < 32 || letter > 126) {
        printf("ERROR: unsupported letter");
        return;
    }
    
    uint8_t font_index = letter - 32;
    if (invert){
        for (uint8_t i = 0; i < 8; i++) {
        uint8_t letter_pixels = pgm_read_byte(&(font8[font_index][i]));
        write_d(~letter_pixels);
        }
    }
    else {
        for (uint8_t i = 0; i < 8; i++) {
        uint8_t letter_pixels = pgm_read_byte(&(font8[font_index][i]));
        write_d(letter_pixels);
        }    
    }
}

void printo(char* string, uint8_t invert){
    for (uint8_t i = 0; string[i] != 0; i++){
        oled_print(string[i], invert);
    }
}

void oled_init() {
    write_c(0xae);  // display off
    write_c(0xa1);  // segment remap
    write_c(0xda);  // common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8);  // common  output scan direction:com63~com0
    write_c(0xa8);  // multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5);  // display  divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81);  // contrast control
    write_c(0x50);
    write_c(0xd9);  // set pre-charge period
    write_c(0x21);
    write_c(0x20);  // Set Memory Addressing Mode
    write_c(0x02);
    write_c(0xdb);  // VCOM deselect level mode
    write_c(0x30);
    write_c(0xad);  // master configuration
    write_c(0x00);
    write_c(0xa4);  // out follows RAM content
    write_c(0xa6);  // set normal display
    write_c(0xaf);  // display on
}

void oled_goto_page(uint8_t page) {
    if (page >= TOTAL_PAGES) {
        printf('\n\rERROR: page out of range. oled_goto_page tried to access page %d', page);
        printf('page reset to 0');
        page = 0;
    }
    write_c(0xb0 + page);
}

void oled_goto_position(uint8_t column, uint8_t page) {
    oled_goto_column(column);
    oled_goto_page(page);
}

void oled_draw_star(){
    oled_reset();
    oled_goto_position(54, 1);
    for (uint8_t i = 0; i < 19; i++) {
        uint8_t letter_pixels = pgm_read_byte(&(star[0][i]));
        write_d(letter_pixels);
    }
    oled_goto_position(54, 2);
    for (uint8_t i = 0; i < 19; i++) {
        uint8_t letter_pixels = pgm_read_byte(&(star[1][i]));
        write_d(letter_pixels);
    }
}

// --------MENU---------

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

// void run_menu(int* bias, char* menu_elements[]){
//     uint8_t current_option = 0;
//     oled_reset(); //put reset here instead of in refresh_menu()
//     refresh_menu(menu_elements, current_option);
//     INPUT input = NEUTRAL;
//     while(1){
//         input = read_input(bias, input);
//         switch (input)
//         {        
//         case UP:
//             if (current_option == 0){
//                 current_option = TOTAL_PAGES - 4;
//             }
//             current_option = current_option - 1;
//             break;
//         case DOWN:
//             current_option = (current_option + 1) % (TOTAL_PAGES - 4);
//             break;
//         case ANALOG_PRESS:
//             switch (current_option){
//                 case 0:

//                 case 1:

//                 case 2:

//                 case 3:
//                     oled_draw_star();
//                     _delay_ms(1000);
//                     run_menu(bias, high_score);

                
//             }

//             oled_draw_star();
//             _delay_ms(1500);
//             oled_reset();
//             break;
//         default:
//             break;
//         }
//         refresh_menu(menu_elements, current_option);
//         _delay_us(10);
//     }
// }

const char high_score_val[16] = "Olve: 999";

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


const char* high_score[TOTAL_PAGES] = {
    "",
    high_score_val,
    "",
    "Back",
    "",
    "",
    "",
    "===HIGH SCORE==="
};

MenuType high_score_menu = {.elements = high_score, .min = 3, .max = 3};
MenuType main_menu = {.elements = main_menu_elem, .min = 0, .max = 3};


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





// uint8_t offset_for_centered_text(char* text){
//     if (strlen(text) > OLED_WIDTH)
// }