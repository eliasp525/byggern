#ifndef PWM_H
#define PWM_H

#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>


void PWM_init();

#endif