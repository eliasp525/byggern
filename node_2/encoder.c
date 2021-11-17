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

    SysTick->LOAD = 84*time_us; //Should reload after time_us. 84 clock cycles per us with 84 Mhz.
	SysTick->VAL = 0;
    SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos);

    SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos); // Enables counter to count down from value in SysTick->LOAD
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // Wait until COUNTFLAG has been set.

    SysTick->CTRL = SysTick->CTRL & !(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_COUNTFLAG_Msk); // Disables counter and clears COUNTFLAG
	SysTick->LOAD = 0;
}

void _delay_ms(uint32_t time_ms){
	//Setup sysTick for delay
	SysTick->CTRL = SysTick->CTRL & !SysTick_CTRL_ENABLE_Msk; // Disables counter

	SysTick->LOAD = 84000*time_ms; //Should reload after time_ms. 84 clock cycles per us with 84 Mhz.
	SysTick->VAL = 0;
	SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos);

	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos); // Enables counter to count down from value in SysTick->LOAD
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // Wait until COUNTFLAG has been set.

	SysTick->CTRL = SysTick->CTRL & !(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_COUNTFLAG_Msk); // Disables counter and clears COUNTFLAG
	SysTick->LOAD = 0; //Try to set this to zero after each delay

}

int16_t get_encoder_value_when_stopped(){
	int16_t encoder_value;
	int16_t prev_encoder_value;
	prev_encoder_value = -1;
	encoder_read(&encoder_value);
	// printf("Encoder value before loop: %x\r\n", encoder_value);
	
	uint32_t count = 0;
	while(encoder_value != prev_encoder_value){
		_delay_ms(100);
		prev_encoder_value = encoder_value;
		encoder_read(&encoder_value);
	}

	set_motor_output_from_joystick_value(0);
	return encoder_value;
}

int16_t get_leftmost_encoder_value(){
	//printf("Getting leftmost encoder value\r\n");
	set_motor_output_from_joystick_value(CALIBRATION_INPUT_TO_MOTORS);
	return get_encoder_value_when_stopped();
}


int16_t get_rightmost_encoder_value(){
	// printf("Getting rightmost encoder value\r\n");
	set_motor_output_from_joystick_value(-CALIBRATION_INPUT_TO_MOTORS);
	
	return get_encoder_value_when_stopped();
}

int16_t convert_encoder_to_joystick(int16_t encoder_value, int16_t leftmost_encoder_value, int16_t rightmost_encoder_value){
	int32_t thousand_a = -((200*1000)/(leftmost_encoder_value-rightmost_encoder_value));
	int32_t thousand_b = 100*1000-thousand_a*rightmost_encoder_value;
	return (thousand_a*encoder_value + thousand_b)/1000;
}