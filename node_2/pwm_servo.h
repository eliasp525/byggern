
#ifndef PWM_SERVO_H
#define PWM_SERVO_H

#include "sam.h"

#define PERIOD_COUNTER 20000
#define NOMINAL_DUTY_CYCLE 18500
#define INPUT_SCALAR 3*PERIOD_COUNTER/10000
#define DIVB_VALUE 21
#define PREB_VALUE 0b001 


void pwm_servo_init();

void pwm_servo_upd_duty_cycle(int8_t duty_cycle);


#endif


#ifndef F_CPU

#define F_CPU 84000000UL

#endif