#include "input.h"

#define I 7
#define SREG 0x3F

void calibrate_joystick_bias(int8_t *bias){
    int x = 0;
    int y = 0;
    for (uint8_t i = 0; i < 10; ++i){
        x += read_adc_channel(X_DIRECTION) - 128;
        y += read_adc_channel(Y_DIRECTION) - 128;

    }

    bias[0] = x/10;
    bias[1] = y/10;
}


void calculate_x_y(int8_t *joystick_position, int8_t *bias){
    uint8_t x = read_adc_channel(X_DIRECTION);
    uint8_t y = read_adc_channel(Y_DIRECTION);
    
    
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


void send_joystick_x_y(int8_t *joystick_position){

    can_msg message = {.id = 69, .data = joystick_position, .len = 2};
    can_send_msg(message);

}


INPUT calculate_direction(int8_t *bias){
    int8_t x = read_adc_channel(X_DIRECTION);
    int8_t y = read_adc_channel(Y_DIRECTION);

    //x = x - bias[0];
    //y = y - bias[1];

    printf("Y: %d \r\n", y);
    printf("X: %d \r\n", x);
    printf("BIAS Y: %d \r\n", bias[1]);
    printf("BIAS X: %d \r\n", bias[0]);

    if (y>78+bias[1] && y<178+bias[1]){
        if (x>178+bias[0]) {return RIGHT;}
        else if (x<78+bias[0]) {return LEFT;} 
        else{return NEUTRAL;}
    }

    else if (x>78+bias[0] && x<178+bias[0]){
        if (y>178+bias[1]) {return UP;}
        else if (y<78+bias[1]) {return DOWN;} 
        else {return NEUTRAL;}
    }
}

INPUT read_input(int8_t *bias, INPUT state){
    while(1){
        INPUT new_state = calculate_direction(bias);
        printf("Input: %d \r\n", new_state);
        if (state != new_state){
            //printf("joystick direction : %d \r\n", new_state);
            return new_state;
        }
        else if (read_joystick_button()){
            _delay_us(5);
            while(read_joystick_button()){
                _delay_us(5);
            }
            
            return ANALOG_PRESS;
        }
        _delay_ms(1000);
    }
}

void read_touch_buttons(uint8_t *buttons){
    buttons[0] = 2 >> (PINB & (1 << PB2));
    buttons[1] = 3 >> (PINB & (1 << PB3));
}

void read_sliders(uint8_t* sliders){
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
    set_bit(MCUCR, ISC00); // INT0 triggers on rising edge

    set_bit(MCUCR, ISC11);
    clear_bit(MCUCR, ISC10); // INT1 triggers on falling edge
}

ISR(INT0_vect){
    int0_flag = 1;
    //printf("interrupt from right button\r\n");
}


