
#include "dac.h"

void dac_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID38; // enable DAC controller clock from PMC
	
	//Reset DACC
	DACC->DACC_CR = DACC_CR_SWRST;
	
    //Free-running mode on channel 1// configure to use whole 32 bits of data conversion register
	DACC->DACC_MR |=  (DACC_MR_TRGEN_DIS | DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_REFRESH(1) | DACC_MR_STARTUP_64); //DACC_MR_WORD;
	DACC->DACC_CDR = 100; //CDR blir ikke satt i det hele tatt, den forblir 0 uansett hva. No idea why tho
	// Setup interrupt for End Of Conversion
	DACC->DACC_IER |= DACC_IER_EOC;
	
	// ENable NVIC
	NVIC_EnableIRQ(DACC_IRQn);
	
	
	
    // enable DAC1 in DACC_CHER
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
}


void dac_convert(uint32_t value){
	DACC->DACC_CDR = value;
}

void DACC_Handler(){
	DACC->DACC_ISR; //Read and clear status register
	if(DACC->DACC_CDR < 4095){
		DACC->DACC_CDR += 1; // Increment by 1 just to test Should give ish sawtooth
	}
	else{
		DACC->DACC_CDR = 0; 
	}
}