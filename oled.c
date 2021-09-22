#include "oled.h"
#include <util/delay.h>

void write_c(uint8_t byte){

   EXTERNAL_MEMORY->OLED_COMMAND[0] = byte;
}

//code implemented from LY190-128064 data sheet
void oled_init()
 {
   write_c(0xae); // display off
   write_c(0xa1); //segment remap - mapping SEG0 to column address 127
   write_c(0x81); //contrast control
   write_c(0xd0);
   write_c(0x20); //Set Memory Addressing Mode
   write_c(0x2);
   write_c(0xd3);
   write_c(0);
   write_c(0xa6); //set normal display
   
   write_c(0xaf); // display on 

   //write_c(0xa5); //entire display ON
   // write_c(0xa4); //entire display OFF
}



void oled_goto_page(uint8_t page){
   //page should range from 0 to 7:
   if( page > 7){
      printf('\n\rERROR: page out of range. oled_goto_page tried to access page %d', page);
      printf('page reset to 0');
      page = 0;
   }
   write_c(0xb0 + page);

}

