#ifndef INPUT_H
#define INPUT_H

#include "adc.h"

#define MAX_AMP 255
#define MIN_AMP 0
#define NO_AMP 128

typedef enum{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
}DIRECTION;

struct position{
    float x;
    float y;
};

void calibrate_joystick_bias(float *bias);

float *calculate_x_y(float *bias);

DIRECTION calculate_direction(float *bias);


#endif