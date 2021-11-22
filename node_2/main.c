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
#include "motor.h"
#include "encoder.h"
#include "systick_timer.h"


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
	can_default_init();
	motor_init();
	encoder_init();
	
	//encoder value
	int16_t encoder_value = 0;
	
	printf("System initialized.\n\r");
	
	// Turn on leds
	PMC->PMC_PCER0 |= PMC_PCER0_PID11;
	PIOA->PIO_PER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	PIOA->PIO_OER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	
	PIOA->PIO_SODR = PIO_PA19;
	PIOA->PIO_SODR = PIO_PA20;
	PIOA->PIO_SODR = PIO_PA14;
	
	// initializing flags
	msg_rec_flag = 0;
	RTT_FLAG = 0;
	int score_counter = 0;
	int score_flag = 0;
	
	int game_mode = 0;
	
	// declaring encoder variables
	int16_t leftmost_encoder_value = 0;
	int16_t rightmost_encoder_value = 0;

	int8_t pid_ref_test = 0;
	int16_t pid_measurement_test = 0;
	
	set_motor_output_from_joystick_value(0);
	
	rtt_init();
    while (1)
    {
		adc_read();
	
		if(RTT_FLAG == 1 && leftmost_encoder_value && rightmost_encoder_value && game_mode == 1){
			pid_measurement_test = convert_encoder_to_joystick(encoder_value, leftmost_encoder_value, rightmost_encoder_value);
			//printf("pid_easurement_test: %d\r\n", pid_measurement_test);
			set_motor_output_from_joystick_value(get_updated_input(pid_measurement_test-pid_ref_test));
			RTT_FLAG = 0;
		}
		
		if (game_mode == 2){
			set_motor_output_from_joystick_value(-pid_ref_test);
		}
		
		if (msg_rec_flag == 1){
			
			if (message.id == 42){
				message.id = 1;
				// printf("Hitting the ball!\r\n ");
				PIOA->PIO_CODR = PIO_PA14;
				_delay_ms(75);
				PIOA->PIO_SODR = PIO_PA14;
				//ball_hit_at = global_rtt_counter;
				//ball_hit_active = 1;
				
				msg_rec_flag = 0;
			}
			
			else if(message.id == 69){
				// printf("x_pos: %d, y_pos %d\r\n", (int8_t)message.data[0], (int8_t)message.data[1]);
				pwm_servo_upd_duty_cycle((int8_t)message.data[1]);
				pid_ref_test = (int8_t)message.data[0];
				msg_rec_flag = 0;
			}
			else if(message.id == 30){
				// starts game
				game_mode = message.data[0];
				calibrate_encoder(&leftmost_encoder_value, &rightmost_encoder_value);
				
				if (game_mode == 1){ // checks if data[0] is 1, which means game mode is timed
					rtt_alarm_start();
					game_over = 0;	
				}
				
				msg_rec_flag = 0;
			}
			
		}
		if (game_over){
			CAN_MESSAGE msg = {.id = 30, .data = 0, .data_length = 1};
			can_send(&msg, 0);
			game_over = 0;
		}
		
		if (analog_value < 5 && !score_flag){  //register a goal
			CAN_MESSAGE msg = {.id = 10, .data = score_counter, .data_length = 1};
			//printf("adc val: %d", analog_value);
			can_send(&msg, 0);
			score_flag = 1;
		}
		else if (analog_value > 300 && score_flag){ //prevent a goal from being registered multiple times
			score_flag = 0;
		}
	
	//if(global_rtt_counter % 100 == 0){
		//printf("Count %d \r\n", 100);
	//}
	
		
		
	encoder_read(&encoder_value);
	
	}
	
}
