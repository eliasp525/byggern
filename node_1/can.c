#include "can.h"

void can_send_msg(can_msg msg){
    mcp_write(MCP_TXB0SIDL, ((msg.id << 5) & 0b11100000));
    //printf("MCP_TXB0SIDL: %d\r\n", mcp_read(MCP_TXB0SIDL));
    mcp_write(MCP_TXB0SIDH, (msg.id >> 3));
    //printf("MCP_TXB0SIDH: %d\r\n", mcp_read(MCP_TXB0SIDH));
    mcp_write(MCP_TXB0DLC, msg.len);
    //printf("MCP_TXB0DLC: %d\r\n", mcp_read(MCP_TXB0DLC));
    mcp_write_buffer(MCP_TXB0D0, msg.data, msg.len);
    mcp_bit_modify(MCP_TXB0CTRL, 0b1000, 0b1000);
    mcp_request_to_send(1,0,0);
    // printf("MCP_TXB0DLC: %d\r\n", mcp_read(MCP_TXB0DLC));
}

void can_recieve_msg(can_msg* message, uint8_t buffer){
    uint8_t start_address;
    switch (buffer)
    {
    case 0:
        start_address = MCP_RXB0D0;
        message->len  = mcp_read(MCP_RXB0DLC) & 0x0F; //Only read last four bits
        break;
    case 1:
        start_address = MCP_RXB1D0;
        message->len = mcp_read(MCP_RXB1DLC) & 0x0F; //Only read last four bits
        break;
    }
    mcp_read_buffer(message, start_address);
}
