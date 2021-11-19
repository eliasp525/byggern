/*
 * timer.h
 *
 * Created: 03.11.2021 11:12:06
 *  Author: adrianop
 */ 


#ifndef RTTIMER_H_
#define RTTIMER_H_

#include "sam.h"
#include "pid_controller.h"

volatile int RTT_FLAG;

uint32_t global_rtt_counter;
uint8_t game_over;

int ball_hit_active;
uint32_t ball_hit_at;

void rtt_alarm_start();

void rtt_init();


#endif /* RTTIMER_H_ */