#include "adc.h"

//AIN0 = Y direction and AIN1 = X direction on joystick
uint8_t read_adc_channel(uint8_t channel_number){
    EXTERNAL_MEMORY->ADC[0] = channel_number | SINGLE_CHANNEL_ADDRESS;
    _delay_us(5);
    volatile uint8_t adc_data = EXTERNAL_MEMORY->ADC[0];
    _delay_us(5);
    return adc_data;
}

