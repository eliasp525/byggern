#include "encoder.h"


void encoder_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; //Enable clock for PIOC
    PMC->PMC_PCER0 |= PMC_PCER0_PID14; //Enable clock for PIOD
    
    PIOD->PIO_PER = (ENCODER_OE | ENCODER_RST | ENCODER_SEL); // Enable pins
    PIOC->PIO_PER = (ENCODER_DO0 | ENCODER_DO1 | ENCODER_DO2 | ENCODER_DO3 | ENCODER_DO4 | ENCODER_DO5 | ENCODER_DO6 | ENCODER_DO7); // Enable parallell data pins

    PIOD->PIO_OER = (ENCODER_OE | ENCODER_RST | ENCODER_SEL); // Set encoder control pins to outputs.
    PIOC->PIO_ODR = (ENCODER_DO0 | ENCODER_DO1 | ENCODER_DO2 | ENCODER_DO3 | ENCODER_DO4 | ENCODER_DO5 | ENCODER_DO6 | ENCODER_DO7); // Set encoder parallel data pins to inputs

    PIOD->PIO_CODR = ENCODER_RST;
    PIOD->PIO_SODR = ENCODER_RST; //Toggle reset of encoder in init.
	
    SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos);
}



void encoder_read(uint32_t *encoder_counter){
    PIOD->PIO_CODR = (ENCODER_OE | ENCODER_SEL); // Set !OE low to enable output of encoder and set SEL low to get high byte
    _delay_us(20);
    *encoder_counter = ((PIOC->PIO_PDSR & ENCODER_DATA_Msk) << 8); //Read high-byte of encoder counter
    PIOD->PIO_SODR = (1 << ENCODER_SEL); //Set SEL high to get low byte of encoder counter
    _delay_us(20);
    *encoder_counter |= (PIOC->PIO_PDSR & ENCODER_DATA_Msk); //Read low-byte of encoder counter
    PIOD->PIO_CODR = ENCODER_RST;
    PIOD->PIO_SODR = ENCODER_RST; //pulse reset of encoder.
    PIOD->PIO_SODR = ENCODER_OE; //Disable output from encoder.
}

void _delay_us(uint32_t time_us){
    //Setup sysTick for delay
    SysTick->CTRL = SysTick->CTRL & !SysTick_CTRL_ENABLE_Msk; // Disables counter

    SysTick-> LOAD = 84*time_us; //Should reload after time_us. 84 clock cycles per us with 84 Mhz.
    SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos);

    SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos); // Enables counter to count down from value in SysTick->LOAD
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // Wait until COUNTFLAG has been set.

    SysTick->CTRL = SysTick->CTRL & !(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_COUNTFLAG_Msk); // Disables counter and clears COUNTFLAG
}