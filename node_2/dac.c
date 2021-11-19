
#include "dac.h"

void dac_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID38; // enable DAC controller clock from PMC
	
	//Reset DACC
	DACC->DACC_CR = DACC_CR_SWRST;
	
    //Free-running mode on channel 1// configure to use whole 32 bits of data conversion register
	DACC->DACC_MR |=  (DACC_MR_TRGEN_DIS | DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_REFRESH(20) | DACC_MR_STARTUP_64); //DACC_MR_WORD;
	
	// Setup interrupt for End Of Conversion
	DACC->DACC_IER |= DACC_IER_EOC;
	
	// ENable NVIC
	NVIC_EnableIRQ(DACC_IRQn);
	
	
	
    // enable DAC1 in DACC_CHER
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	DACC->DACC_CDR = 0;
	
}


void dac_convert(uint32_t value){
	DACC->DACC_CDR = value;
}

void DACC_Handler(){
	DACC->DACC_ISR; //Read and clear status register
	// printf("Running DACC handler\r\n ");
}