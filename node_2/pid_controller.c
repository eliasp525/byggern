#include "pid_controller.h"


void pid_init(uint32_t frequency){
    sum_of_error = 0;
    last_error = 0;
	integration_on = 1;
    sample_frequency = frequency;
}

// e[n] - e[n-1]
int16_t get_updated_input(int16_t err){
	int debug = 0;
	
	int16_t k_p = 8;
	int16_t k_i = 16;
	//int16_t k_d = -20;
	
	if (integration_on == 1){
	    sum_of_error += err;
	}
	
	int16_t proportional_part = (k_p*err) >> 3;
	int16_t integral_part = ((k_i*sum_of_error)/sample_frequency) >> 3;
	//int16_t diff_part = (k_d*(err-last_error))/100;  // *sample_frequency*;
	
    int16_t input = proportional_part + integral_part; // + diff_part;
	
	// anti integrator windup
	if (integration_on == 1 && abs(input) > JOYSTICK_MAX_VAL){
		integration_on = 0;
	}
	else if (integration_on == 0 && abs(input) < JOYSTICK_MAX_VAL){
		integration_on = 1;
	}
	
	last_error = err;
	
	if (debug){
		printf("error: %d\r\n", err);
		printf("sum_of_error: %d\r\n", sum_of_error);
		printf("effect from integral action: %d\r\n", integral_part);
		printf("effect from proportional action: %d\r\n", proportional_part);
		//printf("effect from differentiation action: %d\r\n", diff_part);
		printf("input:  %d\r\n", input);
		printf(" \r\n ");
	}
	
	return input;
}