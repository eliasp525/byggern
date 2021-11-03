/*
 * timer.h
 *
 * Created: 03.11.2021 11:12:06
 *  Author: adrianop
 */ 


#ifndef RTTIMER_H_
#define RTTIMER_H_

#include "sam.h"

volatile int RTT_FLAG;

void rtt_alarm_start();

void rtt_init();

void rtt_check_alarm();


#endif /* RTTIMER_H_ */