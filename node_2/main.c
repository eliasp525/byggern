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
	
	// value for motor
	uint32_t motor_output = 0x000FFFFF;
	// set_motor_output(motor_output);
	
	printf("System initialized.\n\r");
	PMC->PMC_PCER0 |= PMC_PCER0_PID11;
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
	
	//rtt_alarm_start();
	
	
	printf("Starting encoder calibration\r\n ");
	_delay_ms(500);
	int16_t leftmost_encoder_value = get_leftmost_encoder_value();
	printf("Got leftmost value: %d\r\n", leftmost_encoder_value);
	int16_t rightmost_encoder_value = get_rightmost_encoder_value();
	printf("Got rightmost value: %d\r\n", rightmost_encoder_value);
	
	
	int32_t total_range = leftmost_encoder_value - rightmost_encoder_value;
	if (total_range < 0){
		total_range = leftmost_encoder_value + (ENCODER_MAX_VALUE - rightmost_encoder_value);
	}
	
	printf("total range: %d\r\n", total_range);
	int8_t pid_ref_test = 0;
	int16_t pid_measurement_test = 0;
	
	//set_motor_output_from_joystick_value(-100);
	rtt_init();
    while (1) 
    {
		adc_read();
		
		 //testing (safe to remove)
	
		if(RTT_FLAG == 1){
			pid_measurement_test = convert_encoder_to_joystick(encoder_value, leftmost_encoder_value, rightmost_encoder_value);
			set_motor_output_from_joystick_value(get_updated_input(pid_measurement_test-pid_ref_test));
			RTT_FLAG = 0;
		}
					
		 //end testing
		
		if (msg_rec_flag == 1){
			if (message.id == 42){
				message.id = 1;
				PIOA->PIO_CODR = PIO_PA14;
				_delay_ms(100);
				PIOA->PIO_SODR = PIO_PA14;
				printf("Hitting the ball!");
			}
			
			else if(message.id == 69){
				printf("x_pos: %d, y_pos %d\r\n", (int8_t)message.data[0], (int8_t)message.data[1]);
				pwm_servo_upd_duty_cycle((int8_t)message.data[1]);
				pid_ref_test = (int8_t)message.data[0];
				
				//int8_t pid_ref = (int8_t)message.data[0];
				//printf("pid_ref: %d\r\n", pid_ref);
				//int16_t pid_measurement = convert_encoder_to_joystick(encoder_value, leftmost_encoder_value, rightmost_encoder_value);
				//printf("pid_measurement: %d\r\n", pid_measurement);
				//set_motor_output_from_joystick_value(get_updated_input(pid_measurement-pid_ref));
				//msg_rec_flag = 0;
				
				
			}
			
		}
		if (analog_value < 30 && !score_flag){  //&& RTT_FLAG){
			RTT_FLAG = 0;
			//rtt_alarm_start();
			score_counter++;
			CAN_MESSAGE msg = {.id = 10, .data = score_counter, .data_length = 1};
			can_send(&msg, 0);
			printf("Score is: %d\r\n", score_counter);
			score_flag = 1;
		}
		else if (analog_value > 300 && score_flag){ // && RTT_FLAG){
			score_flag = 0;
		}
	encoder_read(&encoder_value);
	// printf("leftmost: %d, rightmost: %d\r\n", leftmost_encoder_value, rightmost_encoder_value);
	// printf("Encoder measurement: %d\r\n", convert_encoder_to_joystick(encoder_value, leftmost_encoder_value, rightmost_encoder_value));
	// printf("Encoder value: %d, %x \r\n", (int16_t)encoder_value, encoder_value);
    // motor_output++;
	//if (motor_output >= 0xFFFFFFFF){
		//motor_output = 0;
	//}
	
	}
	
}
