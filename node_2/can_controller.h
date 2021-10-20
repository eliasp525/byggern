/*
 * can_controller.h
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include <stdint.h>
#define FOSC_NODE_2 84000000
#define BRP 20
#define TIME_QUANTA (2*BRP)/FOSC_NODE_2
#define PHASE_2 5
#define PHASE_1 6
#define SJW 0
#define SMP 0
#define PROPAG 1 // same as prop_seg

typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	char* data;
} CAN_MESSAGE;

uint8_t can_init_def_tx_rx_mb(uint32_t can_br);
uint8_t can_init(uint32_t can_br, uint8_t num_tx_mb, uint8_t num_rx_mb);
uint8_t can_default_init();

uint8_t can_send(CAN_MESSAGE* can_msg, uint8_t mailbox_id);
uint8_t can_receive(CAN_MESSAGE* can_msg, uint8_t mailbox_id);

#endif /* CAN_CONTROLLER_H_ */