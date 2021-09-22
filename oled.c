#include "oled.h"
#include <util/delay.h>

void write_d(uint8_t address, uint8_t data){
    EXTERNAL_MEMORY->OLED_DATA[address] = data;
}

void write_c(uint8_t byte){

   EXTERNAL_MEMORY->OLED_COMMAND[0] = byte;
}

void oled_goto_column(uint8_t column){
    uint8_t lower_nibble = column & 0xF;
    uint8_t upper_nibble = (column >> 4) & 0x1F;
    write_c(lower_nibble);
    write_c(upper_nibble);
}

void oled_home(){
    oled_goto_page(0);
    oled_goto_column(0);
}


//code implemented from LY190-128064 data sheet
void oled_init()
 {
   write_c(0xae); // display off
   write_c(0xa0); //segment remap - mapping SEG0 to column address 127
   write_c(0x81); //contrast control
   write_c(0xd0);
   write_c(0x20); //Set Memory Addressing Mode
   write_c(0x2);
   write_c(0xc0); //set COM output scan direction
   write_c(0xd3); //Set display offset
   write_c(0);
   write_c(0xa6); //set normal display
   
   write_c(0xaf); // display on 

}


