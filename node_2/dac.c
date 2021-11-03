
#include "dac.h"

void dac_init(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID38; // enable DAC controller clock from PMC

    // configure to use whole 32 bits of data conversion register
	DACC->DACC_MR |= DACC_MR_WORD;

    // enable DAC1 in DACC_CHER
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	// select channel 1
	DACC->DACC_MR |= (DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_REFRESH(1));
}


void dac_convert(uint32_t value){
	DACC->DACC_CDR = value;
}