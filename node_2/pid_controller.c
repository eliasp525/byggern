#include "pid_controller.h"


void pid_init(uint32_t frequency){
    sum_of_error = 0;
    last_error = 0;
    sample_frequency = frequency;
}

// e[n] - e[n-1]
uint32_t get_updated_input(uint32_t err){
    sum_of_error += err;
    uint32_t input = K_PROPORTIONAL*err + K_INTEGRAL*sum_of_error/sample_frequency + sample_frequency*K_DERIVATIVE*(err-last_error);
    return input;
}