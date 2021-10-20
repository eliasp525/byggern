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

#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	WDT->WDT_MR = WDT_MR_WDDIS;
	
	can_default_init();
	
	configure_uart();
	PMC->PMC_PCER0 = PMC_PCER0_PID11;
	PIOA->PIO_PER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	PIOA->PIO_OER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
	
	PIOA->PIO_SODR = PIO_PA19;
	PIOA->PIO_SODR = PIO_PA20;
	PIOA->PIO_SODR = PIO_PA14;
	
	
	char rec_data[8] = "";
	CAN_MESSAGE rec_msg = {.data_length = 8, .id = 1, .data = &rec_data};
	uint8_t receive_status = 1; // No received data by default, will be set on receive.
	
	
	printf("System initialized.\n\r");
    while (1) 
    {
		//printf("Hello World\n\r");
		receive_status = can_receive(&rec_msg, 0);
		printf("receive_status = %d \n\r", receive_status);
		if(receive_status == 0) {printf("Received message: ID = %d, length = %d, data[0] = %d\n\r", rec_msg.id, rec_msg.data_length, rec_msg.data[0]);}
		receive_status = 1;
    }
}
