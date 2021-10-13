#ifndef CAN_H_
#define CAN_H_

#include <stdio.h>
#include "mcp2515.h"


void can_send_msg(can_msg msg);

void can_recieve_msg(can_msg* message, uint8_t buffer);


#endif