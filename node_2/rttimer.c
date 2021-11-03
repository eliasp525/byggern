#include "rttimer.h"

const uint32_t AT = 99; //Alarm triggered after AT + 1 counts

void rtt_init(){
	RTT->RTT_MR = RTT_MR_RTTRST | RTT_MR_RTPRES (328) | RTT_MR_RTTINCIEN; //Slow clock is 32,768khz
	RTT->RTT_AR = RTT_AR_ALMV(0xFFFFFFFF);
	NVIC_EnableIRQ(RTT_IRQn);
}

void rtt_alarm_start(){
	RTT->RTT_MR |= RTT_MR_ALMIEN;
	RTT->RTT_AR = RTT_AR_ALMV(AT)
	RTT->RTT_MR |= RTT_MR_RTTRST;
}

void RTT_Handler(){
	RTT->RTT_MR &= ~(RTT_MR_ALMIEN | RTT_MR_RTTINCIEN); //disable interrupts 
	if (RTT->RTT_SR & 0x1){
		RTT_FLAG = 1;
		//printf("RTT Alarm triggered: %d \r\n", RTT_FLAG);
		RTT->RTT_AR = RTT_AR_ALMV(AT);
		RTT->RTT_MR |= RTT_MR_RTTRST;
	}
	else{
		//increment the PI
	}
	
	
	RTT->RTT_MR |= (RTT_MR_RTTINCIEN);
	
}

