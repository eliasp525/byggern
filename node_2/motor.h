
#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"
#include "dac.h"
#include "sam.h"


#define MOTOR_DIR_PIN PIO_PD10
#define MOTOR_EN_PIN PIO_PD9

#define MOTOR_ANALOG_OUTPUT_PIN PIO_PB16 // 0-5 volt
#define MOTOR_DIR 1

void motor_init();

void set_motor_output(uint32_t value);

#endif