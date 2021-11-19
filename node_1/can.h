#ifndef CAN_H_
#define CAN_H_

#include <stdio.h>
#include "mcp2515.h"


void can_send_msg(can_msg msg);

void can_recieve_msg(can_msg* message, uint8_t buffer);

void send_joystick_x_y(int8_t *joystick_position);

#endif