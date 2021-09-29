#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "PWM.h"
#include "adc.h"
#include "bit_operations.h"
#include "constants.h"
#include "external_memory.h"
#include "input.h"
#include "oled.h"
#include "sram_test.h"
#include "uart.h"


#include <util/delay.h> //this must be after constants.h

int main() {
    DDRA = 0;
    USART_init(MYUBRR);

    fdevopen(USART_transmit, USART_receive);

    config_external_memory();

    PWM_init();

    int bias[2];  // X is index 0, Y is index 1
    bias[0] = 0;
    bias[1] = 0;
    calibrate_joystick_bias(bias);

    int position[2];
    position[0] = 0;
    position[1] = 0;

    int buttons[2];
    buttons[0] = 0;
    buttons[1] = 0;

    int slider[2];
    slider[0] = 0;
    slider[1] = 0;

    oled_init();

    oled_reset();
    //led_goto_position(32, 1);

    oled_draw_star();

    // printo("Hello world!", 0);
    // oled_goto_position(0, 3);
    // printo("Hello world!", 1);

    _delay_ms(1500);

    //oled_reset();

    char* menu_elements[TOTAL_PAGES];
    menu_elements[0] = "Option 1";
    menu_elements[1] = "Option 2";
    menu_elements[2] = "Option 3";
    menu_elements[3] = "Exit";
    menu_elements[4] = "";
    menu_elements[5] = "";
    menu_elements[6] = "";
    menu_elements[7] = "===MAIN MENU====";

    run_menu(bias, menu_elements);

    //while (1) {
        // printf("Y: %d \r\n", read_adc_channel(0));
        // printf("X: %d \r\n", read_adc_channel(1));
        // calculate_x_y(position, bias);
        //read_touch_buttons(buttons);
        //printf("\r\nButtons: L: %d,   R: %d", buttons[0], buttons[1]);
        // printf("Bias -  X: %d, Y: %d", bias[0], bias[1]);
        // printf("X: %d, Y: %d \r\n", position[0], position[1]);
        // printf("joystick direction : %d \r\n", calculate_direction(bias));
        // printf("Slider_left: %d \r\n", read_adc_channel(2));
        // printf("Slider_right: %d \r\n", read_adc_channel(3));
        //_delay_ms(500);
    //}

    return 0;
}