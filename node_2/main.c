/*
 * node_2.c
 *
 * Created: 20.10.2021 10:02:59
 * Author : adrianop
 */ 


#include <stdio.h>
#include <stdarg.h>
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "pwm_servo.h"
#include "adc.h"
#include "sam.h"
#include "rttimer.h"
#include "pid_controller.h"



int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	//disable Watchdog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;

	configure_uart();
	
	
	
	
	
	
	pwm_servo_init();
	adc_init();
	pid_init(100);
	rtt_init();
	can_default_init();
	
	printf("System initialized.\n\r");
	
	//enable peripheral clock 11
	PMC->PMC_PCER0 = PMC_PCER0_PID11;
	//Turn on the LEDs on the shield
	PIOA->PIO_PER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	PIOA->PIO_OER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	
	PIOA->PIO_SODR = PIO_PA19;
	PIOA->PIO_SODR = PIO_PA20;
	PIOA->PIO_SODR = PIO_PA14;
	
	
	
	//pwm_servo_upd_duty_cycle(-100);
	msg_rec_flag = 0;
	RTT_FLAG = 0;
	int score_counter = 0;
	int score_flag = 0;
	
	
	rtt_alarm_start();
	
	
    while (1) 
    {
		adc_read();
		
		if (msg_rec_flag == 1){
			if(message.id == 69){
				//printf("x_pos: %d, y_pos %d\r\n", (int8_t)message.data[0], (int8_t)message.data[1]);
				pwm_servo_upd_duty_cycle((int8_t)message.data[0]);
				pid_ref = (int8_t)message.data[1];
				msg_rec_flag = 0;
			}
		}
		if (analog_value < 30 && !score_flag && RTT_FLAG){
			RTT_FLAG = 0;
			rtt_alarm_start();
			score_counter++;
			printf("Score is: %d\r\n", score_counter);
			score_flag = 1;
		}
		else if (analog_value > 300 && score_flag && RTT_FLAG){
			score_flag = 0;
		}
    }
}
