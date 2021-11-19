#include "rttimer.h"


const uint32_t AT = 0; // Alarm triggered after AT + 1 counts

void rtt_init(){
	RTT->RTT_MR = RTT_MR_RTTRST | RTT_MR_RTPRES (328) | RTT_MR_RTTINCIEN; //Slow clock is 32,768khz   // Rtt timer now si 
	RTT->RTT_AR = RTT_AR_ALMV(0xFFFFFFFF);
	NVIC_EnableIRQ(RTT_IRQn);
}

void rtt_alarm_start(){
	RTT->RTT_MR |= RTT_MR_ALMIEN;
	RTT->RTT_AR = RTT_AR_ALMV(AT);
	RTT->RTT_MR |= RTT_MR_RTTRST;
}

void RTT_Handler( void ){
	RTT->RTT_MR &= ~(RTT_MR_ALMIEN | RTT_MR_RTTINCIEN); //disable interrupts 
	RTT_FLAG = 1;
	uint32_t status = RTT->RTT_SR; // have to read status register to clear something, else the entire program stops
	
	RTT->RTT_MR |= RTT_MR_RTTINCIEN;
	NVIC_ClearPendingIRQ(ID_RTT);
	
}

