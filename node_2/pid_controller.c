#include "pid_controller.h"


void pid_init(uint32_t frequency){
    sum_of_error = 0;
    last_error = 0;
    sample_frequency = frequency;
}

// e[n] - e[n-1]
int16_t get_updated_input(int16_t err){
	
	int16_t k_p = 8;
	int16_t k_i = 100;
	int16_t k_d = 75;
	
	int debug = 1;
	
    sum_of_error += err;
	
	int16_t proportional_part = (k_p*err)/10;
	int16_t integral_part = ((k_i*sum_of_error)/10)/sample_frequency;
	int16_t diff_part = (k_d*(err-last_error))/100;  // *sample_frequency*;
	
    int16_t input = proportional_part + integral_part + diff_part;
    
	if (debug){
	    printf("error: %d\r\n", err);
	    printf("sum_of_error: %d\r\n", sum_of_error);
	    printf("effect from integral action: %d\r\n", integral_part);
	    printf("effect from proportional action: %d\r\n", proportional_part);
	    printf("effect from differentiation action: %d\r\n", diff_part);
	    printf("input:  %d\r\n", input);
		printf(" \r\n ");
    }
	
	last_error = err;
	return input;
}