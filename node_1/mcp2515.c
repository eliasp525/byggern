#include "mcp2515.h"

#define RESET_INSTRUCTION 0b11000000
#define READ_INSTRUCTION 0b00000011
#define WRITE_INSTRUCTION 0b00000010
#define RTS_INSTRUCTION(TXB0, TXB1, TXB2) (0b10000000 | TXB0 | (TXB1 << 1 ) | (TXB2 << 2)) //transmit_buffer between 0 and 8
#define BIT_MODIFY_INSTRUCTION 0b00000101
#define READ_STATUS_INSTRUCTION 0b10100000

#define SET_MODE_MASK 0b11100000


void mcp_init(){
    
    spi_master_init();
    mcp_reset();
    // mcp_reset(); 

    uint8_t value = mcp_read(MCP_CANSTAT);
    //printf("((value & SET_MODE_MASK) >> 5): %d\r\n", ((value & SET_MODE_MASK) >> 5));
    if (((value & SET_MODE_MASK) >> 5) != configuration){
        //printf("((value & SET_MODE_MASK) >> 5): %d\r\n", ((value & SET_MODE_MASK) >> 5));
        printf("MCP2515 is not in config mode after reset!\n\r");
        return;
    }

    
    //  configure CANINTE
    mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b00011111);
    //printf("CANINTE: %x\r\n", mcp_read(MCP_CANINTE));

    //configure bit timing in CNFx registers
    mcp_bit_modify(MCP_CNF1, 0xFF, 0x01); //Sets BRP to (1+1), SJW to 1
    mcp_bit_modify(MCP_CNF2, 0xFF, 0b10110001); //Sets PropSeg to (1+1), PS1 to (6+1), SAM to 0 (sample once), BTLMODE to 1 (set PS2 manually)
    mcp_bit_modify(MCP_CNF3, 0x07, 0x05); //Sets PS2 to (5+1)

    // printf("CNF1: %x\r\n", mcp_read(MCP_CNF1));
    // printf("CNF2: %x\r\n", mcp_read(MCP_CNF2));
    // printf("CNF3: %x\r\n", mcp_read(MCP_CNF3));

    //printf("Mode was: %x\r\n", mcp_read(MCP_CANCTRL));
    mcp_set_can_mode(MCP_CANCTRL, normal); // set mode
    //printf("Mode has been set to: %x\r\n", mcp_read(MCP_CANCTRL));

    //printf("CANSTAT: %x\r\n", mcp_read(MCP_CANSTAT));
    
}

void mcp_set_can_mode(uint8_t canctrl, MODES mode){
    //printf("trying to set mode: %d\r\n", mode);
    mcp_bit_modify(canctrl, SET_MODE_MASK, (mode << 5));
}

void mcp_clear_interrupt_bit(uint8_t int_bit){
    mcp_bit_modify(MCP_CANINTF, int_bit, 0);
}

uint8_t mcp_read_interrupt(){
    uint8_t value = mcp_read(MCP_CANSTAT) & 0b1110;
    return value;
}

void mcp_reset(){
    start_transmission();
    spi_master_transceive(RESET_INSTRUCTION);
    end_transmission();
}

unsigned char mcp_read(char address){
    start_transmission();
    spi_master_transceive(READ_INSTRUCTION);
    spi_master_transceive(address);
    unsigned char data = spi_master_transceive(0);
    end_transmission();
    return data;
}

void mcp_write(char address, char data){
    start_transmission();
    spi_master_transceive(WRITE_INSTRUCTION);
    spi_master_transceive(address);
    spi_master_transceive(data);
    end_transmission();
}

void mcp_write_buffer(char start_address, char* data, char len){
    start_transmission();
    spi_master_transceive(WRITE_INSTRUCTION);
    spi_master_transceive(start_address);
    for( char i = 0; i < len+1; i++){
        // printf("TX_DATA[%d]: %c\r\n", i, data[i]);
        spi_master_transceive(data[i]); 
    }
    end_transmission();
}

void mcp_read_buffer(can_msg* message, char start_address){
    start_transmission();
    spi_master_transceive(READ_INSTRUCTION);
    spi_master_transceive(start_address);
    uint8_t len = message->len;
    // printf("Length of message: %d\r\n", len);
    for(uint8_t i = 0; i < len+1; i++){
        // printf("i: %d\r\n", i);
        message->data[i] = spi_master_transceive(0);
        // printf("RX_DATA[%d]: %c\r\n", i, message->data[i]);
    }
    // message->data[len+1] = '\0';
    end_transmission();
}

// Choose which buffer(s) are enabled to send with 
void mcp_request_to_send(uint8_t TXB0, uint8_t TXB1, uint8_t TXB2){
    start_transmission();
    spi_master_transceive(RTS_INSTRUCTION(TXB0, TXB1, TXB2));
    end_transmission();
}

char mcp_read_status(){
    start_transmission();
    spi_master_transceive(READ_STATUS_INSTRUCTION);
    char data = spi_master_transceive(0);
    end_transmission();
    return data;
}

void mcp_bit_modify(char address, char mask, char data){
    start_transmission();
    spi_master_transceive(BIT_MODIFY_INSTRUCTION);
    spi_master_transceive(address);
    spi_master_transceive(mask);
    spi_master_transceive(data);
    end_transmission();
}
