
#include "systick_timer.h"



static void systick_init_us(int period) {
	//set SysTick reload value
	SysTick->LOAD = ((int)(period*84) & SysTick_LOAD_RELOAD_Msk)-1;  
	//reset value on SysTick counter
	SysTick->VAL = 0; 
	//set SysTick priority of interrupts
	NVIC_SetPriority(SysTick_IRQn, IRQ_SysTick_priority);  
	//set SysTick = MCK, enable timer and interrupt                                                            
	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk; 
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;  
}


volatile uint32_t tick_counter = 0;

void _delay_us(uint16_t time_us) {
	tick_counter = time_us;
	systick_init_us(1);
	while(tick_counter != 0);
}


void _delay_ms(uint16_t time_ms) {
	tick_counter = time_ms;
	systick_init_us(1000);
	while(tick_counter != 0);
}


void SysTick_Handler(void) {
	if(tick_counter!=0) {
		tick_counter--;
	}
	else {
		SysTick->CTRL = 0;
	}
}