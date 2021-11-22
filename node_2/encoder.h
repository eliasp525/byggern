
#ifndef ENCODER_H
#define ENCODER_H

#include "sam.h"
#include "motor.h"
#include <stdint.h>
#include "systick_timer.h"

#define ENCODER_MAX_VALUE 0x1FFFF
#define CUT_RANGE_EDGES 200

// PIN-definitions
#define ENCODER_OE PIO_PD0 // active low Output Enable of encoder data
#define ENCODER_RST PIO_PD1 // active low reset of encoder
#define ENCODER_SEL PIO_PD2 // Select low or high byte of encoder output

#define ENCODER_DO0 PIO_PC1 // Parallell data bus bits
#define ENCODER_DO1 PIO_PC2
#define ENCODER_DO2 PIO_PC3
#define ENCODER_DO3 PIO_PC4
#define ENCODER_DO4 PIO_PC5
#define ENCODER_DO5 PIO_PC6
#define ENCODER_DO6 PIO_PC7
#define ENCODER_DO7 PIO_PC8

#define ENCODER_DATA_Msk 0x1fe // To read only PC1-PC8 for encoder data  

#define CALIBRATION_INPUT_TO_MOTORS 90

void encoder_init();
void encoder_read(uint32_t *encoder_counter);

int16_t get_rightmost_encoder_value();
int16_t get_leftmost_encoder_value();
int16_t convert_encoder_to_joystick(int16_t encoder_value, int16_t leftmost_encoder_value, int16_t rightmost_encoder_value);
void calibrate_encoder(int16_t *leftmost_encoder_value, int16_t* rightmost_encoder_value);


#endif