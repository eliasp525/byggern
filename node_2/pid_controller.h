

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#define K_PROPORTIONAL 1
#define K_DERIVATIVE 0
#define K_INTEGRAL 1


#include "stdint.h"

uint32_t sample_frequency;

uint32_t sum_of_error;
uint32_t last_error; // e[n-1]
int8_t pid_ref;

void pid_init(uint32_t smpl_time);

uint32_t get_updated_input(uint32_t err);


#endif