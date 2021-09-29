#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>

#include "adc.h"
#include "constants.h"
#include "util/delay.h"

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL, ANALOG_PRESS } INPUT;

struct position {
    float x;
    float y;
};

void calibrate_joystick_bias(int *bias);

void calculate_x_y(int *position, int *bias);

INPUT calculate_direction(int *bias);

INPUT read_input(int *bias, INPUT state)

void read_touch_buttons(int *buttons);

void read_sliders(int *sliders);

uint8_t read_joystick_button();

#endif