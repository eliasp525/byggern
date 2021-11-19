

#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include <stdint.h>
#include "sam.h"

#define IRQ_SysTick_priority 0

#ifndef F_CPU
#define F_CPU 84000000
#endif

void _delay_us(uint16_t time_us);

void _delay_ms(uint16_t time_ms);


#endif