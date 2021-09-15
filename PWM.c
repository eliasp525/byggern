#include "PWM.h"

void PWM_init(){
    //Setting the TCCR0 timer/Counter0 control-registers:
    TCCR0 = (1 << WGM01)|(1 << COM00)|(1 << CS00);
    //Clear Timer on Compare match (CTC) mode
    //Toggle OC0 on compare match
    // CLK source clk I/O with no prescaling 

    //Set data direction Register to output on OC0:
    DDRB = DDRB|(1 << DDB0);

    
    // Set PWM frequency to F_CPU/(2*OCR0*2)-1
    // freq = 1 228 799 for OCR0 = 1;
    OCR0 = 1;
}

