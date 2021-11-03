
#include "motor.h"

void motor_init(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID12; // IO controller B
    PMC->PMC_PCER0 |= PMC_PCER0_PID14; // IO controller D

    PIOB->PIO_PER = MOTOR_ANALOG_OUTPUT_PIN;
    PIOB->PIO_OER = MOTOR_ANALOG_OUTPUT_PIN;

    PIOD->PIO_PER = (MOTOR_DIR_PIN | MOTOR_EN_PIN);
    PIOD->PIO_OER = (MOTOR_DIR_PIN | MOTOR_EN_PIN);

    PIOD->PIO_SODR = (MOTOR_DIR_PIN | MOTOR_EN_PIN); // set motor direction and enabling motor
}

void set_motor_output(){
    
}