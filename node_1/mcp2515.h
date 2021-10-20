#ifndef MCP2515_H
#define MCP2515_H

#include "spi.h"
#include "mcp2515_registers.h"

typedef struct{
    uint16_t id;
    char* data;
    uint8_t len;
}can_msg;

typedef enum {
    normal = 0b000, 
    sleep = 0b001, 
    loopback = 0b010, 
    listen_only = 0b011, 
    configuration = 0b100
} MODES;


void mcp_init();

void mcp_set_can_mode(uint8_t canctrl, MODES mode);

void mcp_clear_interrupt_bit(uint8_t int_bit);

uint8_t mcp_read_interrupt();

unsigned char mcp_read(char address);

void mcp_write(char address, char data);

// Choose which buffer(s) are enabled to send by setting the corresponding TXBn to 1
void mcp_request_to_send(uint8_t TXB0, uint8_t TXB1, uint8_t TXB2);

void mcp_reset();

char mcp_read_status();

void mcp_bit_modify(char address, char mask, char data);

void mcp_write_buffer(char start_address, char* data, char len);

void mcp_read_buffer(can_msg* message, char start_address);

#endif