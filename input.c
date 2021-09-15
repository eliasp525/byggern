#include "input.h"

void calibrate_joystick_bias(float *bias){
    float x, y = 0;
    for (uint8_t i = 0; i < 10; ++i){
        x += read_adc_channel(X_DIRECTION) - 128;
        y += read_adc_channel(Y_DIRECTION) - 128;
    }

    float bias[0] = x/10;
    float bias[1] = y/10;
}


void calculate_x_y(float *joystick_position, float *bias){
    uint8_t x = read_adc_channel(X_DIRECTION);
    uint8_t y = read_adc_channel(Y_DIRECTION);

    float joystick_position[0] = (x - 128 - bias[0])*100/(-128-bias[0]);
    float joystick_position[1] = (y - 128 - bias[1])*100/(-128-bias[1]);

    // if (x-bias[0] > 128){
    //     //float x_constant_positive = (128 - bias[0])/100;
    //     float x_percent = x*(128 - bias[0])/100
    // }
    // else{
    //     float x_constant_negative = (-128 - bias[0])/100;
    //     float x_percent = x*(-)
    // }
}


DIRECTION calculate_direction(float *bias){
    float x = read_adc_channel(X_DIRECTION) - bias[0];
    float y = read_adc_channel(Y_DIRECTION) - bias[1];

    if (y > 98 && y <158){
        if (x > 158) {return RIGHT;}
        else{return LEFT;}
    }

    else if (x > 98 && x < 158){
        if (y > 158) {return UP;}
        else {return DOWN;}
    }

    else {return NEUTRAL;}

}