#include "adc.h"

uint8_t read_adc_channel(uint8_t channel_number){
    uint8_t channel_address = channel_number | SINGLE_CHANNEL_ADDRESS;
    EXTERNAL_MEMORY->ADC[0] = channel_address;
    _delay_us(5);
    volatile uint8_t adc_data = EXTERNAL_MEMORY->ADC[0];
    return adc_data;
}

