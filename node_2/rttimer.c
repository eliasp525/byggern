#include "rttimer.h"


const uint32_t AT = 299; // Alarm triggered after AT + 1 counts

void rtt_init(){
	RTT->RTT_MR = RTT_MR_RTTRST | RTT_MR_RTPRES (3276) | RTT_MR_RTTINCIEN; //Slow clock is 32,768khz   // RTT_MR_RTPRES (328) => 100 Hz, RTT_MR_RTPRES (32768) => 1 Hz
	RTT->RTT_AR = RTT_AR_ALMV(0xFFFFFFFF);
	NVIC_EnableIRQ(RTT_IRQn);
	
	
	ball_hit_active = 0;
	ball_hit_at = 0;
}

void rtt_alarm_start(){
	RTT->RTT_MR |= RTT_MR_ALMIEN;
	RTT->RTT_AR = RTT_AR_ALMV(AT);
	RTT->RTT_MR |= RTT_MR_RTTRST;
}

void RTT_Handler( void ){
	RTT->RTT_MR &= ~(RTT_MR_ALMIEN | RTT_MR_RTTINCIEN); //disable interrupts 
	RTT_FLAG = 1;
	
	if (RTT->RTT_SR & 1){ //read SR and check if alarm was triggered
		RTT->RTT_AR = RTT_AR_ALMV(0xFFFFFFFF);
		game_over = 1;
	}
	
	if (global_rtt_counter > 4294967294){
		global_rtt_counter = 0;
	}
	else{
		global_rtt_counter++;
	}
	
	
	// turn off solenoid after x cycles of RTT
	//if (ball_hit_active && (global_rtt_counter > (ball_hit_at + 30))){
		//// printf("Ball hit at: %d\r\n", ball_hit_at);
		//// printf("Current global rtt counter %d\r\n", global_rtt_counter);
		//PIOA->PIO_SODR = PIO_PA14;
		//ball_hit_active = 0;
	//}
	
	
	
	//if(global_rtt_counter % 1 == 0){
		//printf("Count %d \r\n", 1);
	//}
	
	RTT->RTT_MR |= RTT_MR_RTTINCIEN;
	NVIC_ClearPendingIRQ(ID_RTT);
	
}

