#include <avr/io.h>
#include "uart.h"
#define F_CPU 4915200
#include <util/delay.h>


#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg  &= ~(1<<bit))
#define test_bit(reg, bit) (reg & (1 << bit))
//#define loop_until_bit_is_set(reg, bit) while(!test_bit(reg ,bit))
//#define loop_until_bit_is_clear(reg, bit) while(test_bit(reg ,bit))

int main(){
    // DDRA = 0;
    // for (int i = 0; i < 1000; i++)
    // {
    //     set_bit(PORTA,1);
    //     _delay_ms(100);
    //     clear_bit(PORTA,1);
    //     _delay_ms(100);
    // }

    USART_init(MYUBRR);

    USART_transmit("a");

    return 0;
}