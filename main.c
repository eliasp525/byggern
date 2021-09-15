#define F_CPU 4915200
#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit_operations.h"
#include "external_memory.h"
#include "sram_test.h"
#include "PWM.h"
#include "adc.h"

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

    //SRAM_test();

    PWM_init();

    

    while(1){
        //printf("Y: %d \r\n", read_adc_channel(0));
        //printf("X: %d \r\n", read_adc_channel(1));
        printf("Slider_left: %d \r\n", read_adc_channel(2));
        printf("Slider_right: %d \r\n", read_adc_channel(3));
        _delay_ms(50git0);
    }

    return 0;
}