#include "pwm_servo.h"

// Importantregisters:
// - PWM_CLK :PWMClockregister
// - REG_PWM_CMRn :PWMChannelModeRegister
// - REG_PWM_CPRDn :PWMChannelPeriodRegister
// - REG_PWM_CDTYn :PWMChannelDutyCycleRegister
// - PWM_ENA :PWMEnableRegister


void pwm_servo_init(){
    PIOC->PIO_PDR = (1 << PIO_PC19); //Disable PIO control of pin PC19 (pin44), so that pwm can control it
    PIOC->PIO_ABSR |= (1 << PIO_PC19); //Assign peripheral B function

    // enable PMC   
    PWM->PWM_CLK |= (PREB_VALUE << 24) | (DIVB_VALUE << 16);
    PWM->REG_PWM_CMR0 |= (0b1100) | (1 << PWM_CALG);
    PWM->REG_PWM_CPRD0 = PERIOD_COUNTER; //This should give a freq of 50hz
    PWM->REG_PWM_CDTY0 = NOMINAL_DUTY_CYCLE; //this gives duty cycle(CPRD/CDTY) = 1,5/20
    PWM->PWM_ENA = 1;

}

void pwm_servo_upd_duty_cycle(uint8_t input){
    PWM->REG_PWM_CDTYUPD0 = NOMINAL_DUTY_CYCLE + input * INPUT_SCALAR;
}