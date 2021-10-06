#include "mcp2515.h"

#define RESET_INSTRUCTION 0b11000000
#define READ_INSTRUCTION 0b00000011
#define WRITE_INSTRUCTION 0b00000010
#define RTS_INSTRUCTION(TXB0, TXB1, TXB2) (0b10000000 | TXB0 | (TXB1 << 1 ) | (TXB2 << 2)) //transmit_buffer between 0 and 8
#define BIT_MODIFY_INSTRUCTION 0b00000101
#define READ_STATUS_INSTRUCTION 0b10100000


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

void mcp_write_array(char start_address, char* data, char len){
    start_transmission();
    spi_master_transceive(WRITE_INSTRUCTION);
    spi_master_transceive(start_address);
    for( char i = 0; i < len; i ++){
       spi_master_transceive(data[i]); 
    }
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