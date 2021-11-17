

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#define K_PROPORTIONAL 4
#define K_DERIVATIVE 0
#define K_INTEGRAL 0

// #define APPLICABLE_ENCODER_RANGE 0x4849 // the range of values the encoder will take when moving 'bumper' from left to right on rails


#include "stdint.h"

int16_t sample_frequency;

int32_t sum_of_error;
int16_t last_error; // e[n-1]
int8_t pid_ref;

void pid_init(uint32_t frequency);

int16_t get_updated_input(int16_t err);


#endif