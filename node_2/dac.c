
#include "dac.h"

void dac_init(){
    PMC->PMC_PCER1 |= PMC_PCER0_PID38; // enable DAC controller clock from PMC

    // configure to use whole 32 bits of data conversion register
    // DAC->DACC_MR |= DACC_CDR_WORD;

    // enable DAC1 in DACC_CHER
    // guessing this is something like:
    // DAC->DACC_CHER |= DACC_CHER_CH1;


}


void dac_convert(uint32_t value){
    // DAC->DACC_DCR = value;
}