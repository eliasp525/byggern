#include "input.h"

#define I 7
#define SREG 0x3F

void calibrate_joystick_bias(int *bias){
    int x = 0;
    int y = 0;
    for (uint8_t i = 0; i < 10; ++i){
        x += read_adc_channel(X_DIRECTION) - 128;
        y += read_adc_channel(Y_DIRECTION) - 128;

    }

    bias[0] = x/10;
    bias[1] = y/10;
}


void calculate_x_y(int *joystick_position, int *bias){
    int x = read_adc_channel(X_DIRECTION);
    int y = read_adc_channel(Y_DIRECTION);
    
    if(x - bias[0] - 128 > 0){
        joystick_position[0] = (x - bias[0] - 128)*100/(127-bias[0]);
    }
    else{
        joystick_position[0] = (x - bias[0] - 128)*100/(126+bias[0]);
    }
    if(y - bias[1] - 128 > 0){
        joystick_position[1] = (y - bias[1] - 128)*100/(127-bias[1]);
    }
    else{
        joystick_position[1] = (y - bias[1] - 128)*100/(126+bias[1]);
    }
    
}


INPUT calculate_direction(int *bias){
    int x = read_adc_channel(X_DIRECTION) - bias[0];
    int y = read_adc_channel(Y_DIRECTION) - bias[1];

    //printf("Y: %d \r\n", y);
    //printf("X: %d \r\n", x);
    //printf("BIAS Y: %d \r\n", bias[1]);
    //printf("BIAS X: %d \r\n", bias[0]);

    if (y > 78 && y <178){
        if (x > 178) {return RIGHT;}
        else if (x < 78) {return LEFT;}
        else{return NEUTRAL;}
    }

    else if (x > 78 && x < 178){
        if (y > 178) {return UP;}
        else {return DOWN;}
    }
}

INPUT read_input(int *bias, INPUT state){
    while(1){
        INPUT new_state = calculate_direction(bias);
        if (state != new_state){
            //printf("joystick direction : %d \r\n", new_state);
            return new_state;
        }
        else if (!read_joystick_button()){
            _delay_us(5);
            while(!read_joystick_button()){
                _delay_us(5);
            }
            
            return ANALOG_PRESS;
        }
        _delay_ms(500);
    }
}

void read_touch_buttons(int *buttons){
    buttons[0] = 2 >> (PINB & (1 << PB2));
    buttons[1] = 3 >> (PINB & (1 << PB3));
}

void read_sliders(int* sliders){
    sliders[0] = read_adc_channel(3); 
    sliders[1] = read_adc_channel(4); 
}

uint8_t read_joystick_button(){
    return  (1 >> !(PIND & ( 1 << PD2))); //is pulled low on trigger

}

void interrupt_init(){
    sei(); //Global interrupt enable flag.
    GICR = (1 << INT0)|(1 << INT1); // INT0 and INT1 external interrupt enabled 

    set_bit(MCUCR, ISC01);
    clear_bit(MCUCR, ISC00); // INT0 triggers on falling edge

    set_bit(MCUCR, ISC11);
    clear_bit(MCUCR, ISC10); // INT1 triggers on falling edge
}

ISR(INT0_vect){
    printf("interrupt 0 triggered\r\n");
}


