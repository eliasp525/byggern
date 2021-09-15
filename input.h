#ifndef INPUT_H
#define INPUT_H

#include "adc.h"
#include <stdlib.h>
#include <stdint.h>

#define MAX_AMP 255
#define MIN_AMP 0
#define NO_AMP 128
#define Y_DIRECTION 0
#define X_DIRECTION 1

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

void calibrate_joystick_bias(int *bias);

void calculate_x_y(int *position, int *bias);

DIRECTION calculate_direction(int *bias);


#endif