
#include "motor.h"

void motor_init(){
	dac_init();
    PMC->PMC_PCER0 |= PMC_PCER0_PID12; // IO controller B
    PMC->PMC_PCER0 |= PMC_PCER0_PID14; // IO controller D

    PIOB->PIO_PER = MOTOR_ANALOG_OUTPUT_PIN;
    PIOB->PIO_OER = MOTOR_ANALOG_OUTPUT_PIN;

    PIOD->PIO_PER = (MOTOR_DIR_PIN | MOTOR_EN_PIN);
    PIOD->PIO_OER = (MOTOR_DIR_PIN | MOTOR_EN_PIN);

    PIOD->PIO_SODR = (MOTOR_DIR_PIN | MOTOR_EN_PIN); // set motor direction and enabling motor
}

void set_motor_output(uint32_t value){
    dac_convert(value);
}

void set_motor_direction(int8_t dir){
	// dir = 1 or 0
	if (dir > 0){
		PIOD->PIO_CODR = MOTOR_DIR_PIN;
	}
	else if (dir < 0){
		PIOD->PIO_SODR = MOTOR_DIR_PIN;
	}
}


void set_motor_output_from_joystick_value(int16_t joystick_value){
	set_motor_direction(joystick_value);
	
	if (abs(joystick_value) > 100){
		joystick_value = 100;
	}
	
	int16_t value_applied_saturation = (SATURATE_JOYSTICK_AT*abs(joystick_value))/JOYSTICK_MAX_VAL; // value_applied_saturation maps 0-JOYSTICK_MAX_VAL(=100) to 0-SATURATE_JOYSTICK_AT(=30)
	int16_t motor_output =  (DAC_RESOLUTION/JOYSTICK_MAX_VAL)*value_applied_saturation;
	
	// printf("Setting motor output to %d \r\n", motor_output);
	
	set_motor_output(motor_output);
}