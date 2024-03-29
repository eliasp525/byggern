#include "can.h"

void can_send_msg(can_msg msg){
    mcp_write(MCP_TXB0SIDL, ((msg.id << 5) & 0b11100000));
    mcp_write(MCP_TXB0SIDH, (msg.id >> 3));
    mcp_write(MCP_TXB0DLC, msg.len);
    mcp_write_buffer(MCP_TXB0D0, msg.data, msg.len);
    mcp_bit_modify(MCP_TXB0CTRL, 0b1000, 0b1000);
}

void can_recieve_msg(can_msg* message, uint8_t buffer){
    uint8_t start_address;
    switch (buffer)
    {
    case 0:
        start_address = MCP_RXB0D0;
        message->len  = mcp_read(MCP_RXB0DLC) & 0x0F; //Only read last four bits
        message->id = (mcp_read(MCP_RXB0SIDL) >> 5) + (mcp_read(MCP_RXB0SIDH) << 3);
        break;
    case 1:
        start_address = MCP_RXB1D0;
        message->len = mcp_read(MCP_RXB1DLC) & 0x0F; //Only read last four bits
        message->id = (mcp_read(MCP_RXB1SIDL) >> 5) + (mcp_read(MCP_RXB1SIDH) << 3);
        break;
    }
    mcp_read_buffer(message, start_address);
}

void send_joystick_x_y(int8_t *joystick_position){

    can_msg message = {.id = 69, .data = joystick_position, .len = 2};
    can_send_msg(message);

}
