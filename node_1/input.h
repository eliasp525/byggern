#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "can.h"
#include "adc.h"
#include "constants.h"
#include "bit_operations.h"

volatile int int0_flag;

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL, ANALOG_PRESS } INPUT;


void calibrate_joystick_bias(int8_t *bias);

void calculate_x_y(int8_t *position, int8_t *bias);

INPUT calculate_direction(int8_t *bias);

INPUT read_input(int8_t *bias, INPUT state);

void read_touch_buttons(uint8_t *buttons);

void read_sliders(uint8_t *sliders);

uint8_t read_joystick_button();

void interrupt_init();

#endif