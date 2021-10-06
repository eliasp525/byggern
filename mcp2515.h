#ifndef MCP2515_H
#define MCP2515_H

#include "spi.h"

void init_mcp();

char read_mcp(char address);

void write_mcp(char address, char data);

void request_to_send();

#endif