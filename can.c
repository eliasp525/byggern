#include "can.h"

#define CNF1 0x28
#define CNF2 0x29
#define CNF3 0x2A
#define TXRTSCTRL 0x0D

#define CANCTRLB 0b00111111
#define CANINTE 0x2B
#define CANINTF 0x2C

#define SET_MODE_MASK 0b11100000

void can_init(){
    // set to configure mode
    //  do configure stuff
    
    spi_master_init();
    mcp_reset();
    mcp_reset(); 

    uint8_t value = mcp_read(MCP_CANSTAT);
    printf("((value & SET_MODE_MASK) >> 5): %d\r\n", ((value & SET_MODE_MASK) >> 5));
    if (((value & SET_MODE_MASK) >> 5) != configuration){
        printf("((value & SET_MODE_MASK) >> 5): %d\r\n", ((value & SET_MODE_MASK) >> 5));
        printf("MCP2515 is not in config mode after reset!\n\r");
        return;
    }

    
    //  configure CANINTE
    mcp_bit_modify(MCP_CANINTE, 0b11111, 0b11111);
    printf("CANINTE: %x\r\n", mcp_read(MCP_CANINTE));

    //  set CNF1, CNF2, CNF3 with bit_modify ?
    //  TXRTSCTRL ?
    printf("Mode was: %x\r\n", mcp_read(MCP_CANCTRL));
    can_set_mode(MCP_CANCTRL, loopback); // set to loopback mode
    printf("Mode has been set to: %x\r\n", mcp_read(MCP_CANCTRL));

    printf("CANSTAT: %x\r\n", mcp_read(MCP_CANSTAT));
    
}

void can_set_mode(uint8_t canctrl, MODES mode){
    printf("trying to set mode: %d\r\n", mode);
    mcp_bit_modify(canctrl, SET_MODE_MASK, (mode << 5));
}

void can_send_msg(can_msg msg){
    mcp_write(MCP_TXB0SIDL, ((msg.id << 5) & 0b11100000));
    printf("MCP_TXB0SIDL: %d\r\n", mcp_read(MCP_TXB0SIDL));
    mcp_write(MCP_TXB0SIDH, (msg.id >> 3));
    printf("MCP_TXB0SIDH: %d\r\n", mcp_read(MCP_TXB0SIDH));
    mcp_write(MCP_TXB0DLC, msg.len);
    printf("MCP_TXB0DLC: %d\r\n", mcp_read(MCP_TXB0DLC));
    mcp_write_array(MCP_TXB0D0, msg.data, msg.len);
    mcp_bit_modify(MCP_TXB0CTRL, 0b1000, 0b1000);
        // printf("MCP_TXB0DLC: %d\r\n", mcp_read(MCP_TXB0DLC));
}


uint8_t can_recieve_msg(){

}

void clear_interrupt_bit(uint8_t int_bit){
    mcp_bit_modify(MCP_CANINTF, int_bit, 0);
}

uint8_t read_interrupt_source(){
    uint8_t value = mcp_read(MCP_CANSTAT) & 0b111;
    printf("value interrupt: %d\r\n", value);
    return value;
}