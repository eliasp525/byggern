#include "pwm_servo.h"

void pwm_servo_init(){
    PIOC->PIO_PDR = PIO_PC19; //Disable PIO control of pin PC19 (pin44), so that pwm can control it
    PIOC->PIO_ABSR |= PIO_PC19; //Assign peripheral B function

    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // enable PMC   
    
	PWM->PWM_CLK |= (PREB_VALUE << 24) | (DIVB_VALUE << 16); //PWM clock to 2Mhz
    REG_PWM_CMR5 |= (0b1100) | PWM_CMR_CALG;
    REG_PWM_CPRD5 = PERIOD_COUNTER; //This should give a freq of 50hz
    REG_PWM_CDTY5 = NOMINAL_DUTY_CYCLE; //this gives duty cycle(CPRD/CDTY) = 1,5/20
    PWM->PWM_ENA = 1 << 5;
	

}

void pwm_servo_upd_duty_cycle(int8_t input){
	if (input > 100){
		input = 100;
	}
	else if (input < -100){
		input = -100;	
	}
	else if (input*input < 5){
		input = 0;
	}
    REG_PWM_CDTYUPD5 = NOMINAL_DUTY_CYCLE + input * INPUT_SCALAR;
}