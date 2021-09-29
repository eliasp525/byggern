#include "input.h"

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

    if (y > 98 && y <158){
        if (x > 158) {return RIGHT;}
        else if (x < 98) {return LEFT;}
        else{return NEUTRAL;}
    }

    else if (x > 98 && x < 158){
        if (y > 158) {return UP;}
        else {return DOWN;}
    }
}

INPUT read_input(int *bias, INPUT state){
    while(1){
        INPUT new_state = calculate_direction(bias);
        if (state != new_state){
            return new_state;
        }
        else if (!read_joystick_button()){
            _delay_us(5);
            while(!read_joystick_button()){
                _delay_us(5);
            }
            return ANALOG_PRESS;
        }
        _delay_us(5);
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
    return  (2 >> !(PIND & ( 1 << PD2))); //is pulled low on trigger
}

// How's it going?
// går bra, vi får displaya "hello world!" på oledn!!
// Konge!
//Det e en chat hvis vi trykke på luuveshare på si