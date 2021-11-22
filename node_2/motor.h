
#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"
#include "dac.h"
#include "sam.h"


#define MOTOR_DIR_PIN PIO_PD10
#define MOTOR_EN_PIN PIO_PD9

#define MOTOR_ANALOG_OUTPUT_PIN PIO_PB16 // 0-5 volt

#define JOYSTICK_MAX_VAL 100
#define SATURATE_JOYSTICK_AT 35
#define JOYSTICK_FULL_RANGE JOYSTICK_MAX_VAL*2

void motor_init();

void set_motor_output(uint32_t value);

void set_motor_direction(int16_t dir);

void set_motor_output_from_joystick_value(int16_t joystick_value);

#endif