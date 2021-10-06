#include "mcp2515.h"

#define RESET_INSTRUCTION 0b11000000
#define READ_INSTRUCTION 0b00000011
#define WRITE_INSTRUCTION 0b00000010
#define RTS_INSTRUCTION(TXB0, TXB1, TXB2) (0b10000000 | (TXB0 | (1<<TXB1) | (2<<TXB2)))
#define set_bit(reg, bit) (reg |= (1 << bit))
#define BIT_MODIFY_INSTRUCTION 0b00000101

void init_mcp(){

}

void reset_mcp(){
    start_transmission();
    spit_master_transceive(RESET_INSTRUCTION);
    end_transmission();
}

char read_mcp(char address){
    start_transmission();
    spi_master_transceive(READ_INSTRUCTION);
    spi_master_transceive(address);
    char data = spi_master_transceive(0);
    end_transmission();
    return data;
}

void write_mcp(char address, char data){
    start_transmission();
    spi_master_transceive(WRITE_INSTRUCTION);
    spi_master_transceive(address);
    spi_master_transceive(data);
    end_transmission();
}

void request_to_send(){
    start_transmission();
    spi_master_transceive()
    end_transmission();
}
