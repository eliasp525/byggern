#ifndef MCP2515_H
#define MCP2515_H

#include "spi.h"
#include "mcp2515_registers.h"

unsigned char mcp_read(char address);

void mcp_write(char address, char data);

// Choose which buffer(s) are enabled to send by setting the corresponding TXBn to 1
void mcp_request_to_send(uint8_t TXB0, uint8_t TXB1, uint8_t TXB2);

void mcp_reset();

char mcp_read_status();

void mcp_bit_modify(char address, char mask, char data);

void mcp_write_array(char start_address, char* data, char len);

#endif