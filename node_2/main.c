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



int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	WDT->WDT_MR = WDT_MR_WDDIS;
	
	
	configure_uart();
	can_default_init();
	printf("System initialized.\n\r");
	PMC->PMC_PCER0 = PMC_PCER0_PID11;
	PIOA->PIO_PER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	PIOA->PIO_OER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	
	PIOA->PIO_SODR = PIO_PA19;
	PIOA->PIO_SODR = PIO_PA20;
	//PIOA->PIO_SODR = PIO_PA14;
	
	pwm_servo_init();
	
	pwm_servo_upd_duty_cycle(100);
	
	adc_init();
	//char rec_data[8] = "";
	//CAN_MESSAGE rec_msg = {.data_length = 8, .id = 1, .data = &rec_data};
    while (1) 
    {
		if(message.id == 69){
			// printf("x_pos: %d, y_pos %d\r\n", (int8_t)message.data[0], (int8_t)message.data[1]);
			// pwm_servo_upd_duty_cycle((int8_t)message.data[0]);
		}
		adc_read();
		
    }
}
