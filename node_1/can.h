#ifndef CAN_H_
#define CAN_H_

#include <stdio.h>
#include "mcp2515.h"

typedef enum {
    normal = 0b000, 
    sleep = 0b001, 
    loopback = 0b010, 
    listen_only = 0b011, 
    configuration = 0b100
} MODES;

void can_init();

void can_set_mode(uint8_t canctrl, MODES mode);

void can_send_msg(can_msg msg);

void can_recieve_msg(can_msg* message, uint8_t buffer);

void clear_interrupt_bit(uint8_t int_bit);

uint8_t read_interrupt_source();




#endif