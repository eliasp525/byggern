#include "adc.h"

void adc_init(){
	
	// Enable PMC
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	
	// reset ADC
	ADC->ADC_CR = ADC_CR_SWRST;
	
	//// disable in pio
	//PIOA->PIO_PDR = PIOA
	
	// configure mode register
	ADC->ADC_MR |= ADC_MR_LOWRES;
	
	// enable data ready interrupt
	ADC->ADC_IER |= ADC_IER_EOC0;
	
	//Enable adc interrupts
	NVIC_EnableIRQ(ADC_IRQn);
	
	// enable channel 0
	ADC->ADC_CHER |= ADC_CHER_CH0;
	
}

void adc_read(){
	// start reading adc
	ADC->ADC_CR |= ADC_CR_START;
}


void ADC_Handler(void){
	analog_value = ADC->ADC_CDR[0];
	//printf("Analog value: %d\r\n", analog_value);
	//NVIC_ClearPendingIRQ(ID_ADC);
}