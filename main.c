#define F_CPU 4915200
#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit_operations.h"
#include "external_memory.h"
#include "sram_test.h"
#include "input.h"
#include "PWM.h"
#include "adc.h"
#include "oled.h"

int main(){
    DDRA = 0;
    USART_init(MYUBRR);

    fdevopen(USART_transmit, USART_receive);
    // for (int i = 0; i < 5; i++)
    // {
    //     set_bit(PORTA,1);
    //     _delay_ms(100);
    //     clear_bit(PORTA,1);
    //     _delay_ms(100);
    //     // printf("f ord\n");
    // }

    // USART_transmit(USART_receive());

    config_external_memory();
    
    // EXTERNAL_MEMORY->SRAM[0] = 0xFF;
    // printf( "Value: %d \r\n", EXTERNAL_MEMORY->SRAM[0]);

    PWM_init();

    //SRAM_test();
    int bias[2];  //X is index 0, Y is index 1
    bias[0] = 0;
    bias[1] = 0;
    calibrate_joystick_bias(bias);

    int position[2];
    position[0] = 0;
    position[1] = 0;

    int buttons[2];
    buttons[0] = 0;
    buttons[1] = 0;

    
    oled_init();
    
    for(int j = 0; j < 3; j++){
        int addr = 0xb0 + j;
        for(int i = 0; i < 127; i++){
            EXTERNAL_MEMORY->OLED_DATA[i] = 0xFF;
            EXTERNAL_MEMORY->OLED_DATA[i+1] = 0x00;
        }
        write_c(addr);
    }
    for(int j = 3; j < 8; j++){
        int addr = 0xb0 + j;
        for(int i = 1; i < 127; i++){
            EXTERNAL_MEMORY->OLED_DATA[i] = 0x00;
        }
        write_c(addr);
    } 
    


    while(1){
        //printf("Y: %d \r\n", read_adc_channel(0));
        //printf("X: %d \r\n", read_adc_channel(1));
        //calculate_x_y(position, bias);
        read_touch_buttons(buttons);
        printf("\r\nButtons: L: %d,   R: %d", buttons[0], buttons[1]);
        //printf("Bias -  X: %d, Y: %d", bias[0], bias[1]);
        //printf("X: %d, Y: %d \r\n", position[0], position[1]);
        //printf("joystick direction : %d \r\n", calculate_direction(bias));
        //printf("Slider_left: %d \r\n", read_adc_channel(2));
        //printf("Slider_right: %d \r\n", read_adc_channel(3));
        _delay_ms(500);
    }

    return 0;
}