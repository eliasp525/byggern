

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "stdint.h"
#include "motor.h"

int16_t sample_frequency;

int32_t sum_of_error;
int16_t last_error; // e[n-1]
int8_t pid_ref;

uint8_t integration_on;

void pid_init(uint32_t frequency);

int16_t get_updated_input(int16_t err);


#endif