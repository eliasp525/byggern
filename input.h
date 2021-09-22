#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>

#include "adc.h"
#include "constants.h"

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL } DIRECTION;

struct position {
    float x;
    float y;
};

void calibrate_joystick_bias(int *bias);

void calculate_x_y(int *position, int *bias);

DIRECTION calculate_direction(int *bias);

void read_touch_buttons(int *buttons);

void read_sliders(int *sliders);

uint8_t read_joystick_button();

#endif