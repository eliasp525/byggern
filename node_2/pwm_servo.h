
#ifndef PWM_SERVO_H
#define PWM_SERVO_H

#define PERIOD_COUNTER 40000
#define NOMINAL_DUTY_CYCLE 3000
#define INPUT_SCALAR 3*PERIOD_COUNTER/100
#define DIVB_VALUE 21
#define PREB_VALUE 0b001 

void pwm_servo_init();

void pwm_servo_set_duty_cycle(uint8_t duty_cycle);


#endif