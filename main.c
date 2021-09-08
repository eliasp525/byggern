#define F_CPU 4915200
#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include "bit_operations.h"
#include "external_memory.h"
#include "sram_test.h"

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

    SRAM_test();

    while(1);

    return 0;
}