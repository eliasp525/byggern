#include "pid_controller.h"


void pid_init(uint32_t frequency){
    sum_of_error = 0;
    last_error = 0;
    sample_frequency = frequency;
}

// e[n] - e[n-1]
int16_t get_updated_input(int16_t err){
	printf("Error PID: %d\r\n", err);
    sum_of_error += err;
    int16_t input = K_PROPORTIONAL*err + K_INTEGRAL*sum_of_error/sample_frequency + sample_frequency*K_DERIVATIVE*(err-last_error);
    printf("Input: %d\r\n", input);
	return input;
}