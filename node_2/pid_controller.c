#include "pid_controller.h"


void pid_init(uint32_t smpl_time){
    sum_of_error = 0;
    last_error = 0;
    sampling_time = smpl_time;
}

// e[n] - e[n-1]
uint32_t get_updated_input(uint32_t err){
    sum_of_error += err;
    uint32_t input = K_PROPORTIONAL*err + sampling_time*K_INTEGRAL*sum_of_error + (K_DERIVATIVE/sampling_time)*(err-last_error);
    return input
}