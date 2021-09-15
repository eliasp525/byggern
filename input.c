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
        joystick_position[0] = (x - bias[0] - 128)*100/(128-bias[0]);
    }
    else{
        joystick_position[0] = (x - bias[0] - 128)*100/(128+bias[0]);
    }
    if(y - bias[1] - 128 > 0){
        joystick_position[1] = (y - bias[1] - 128)*100/(128-bias[1]);
    }
    else{
        joystick_position[1] = (y - bias[1] - 128)*100/(128+bias[1]);
    }
    
}


DIRECTION calculate_direction(int *bias){
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
uint