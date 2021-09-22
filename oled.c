#include "oled.h"

//code implemented from LY190-128064 data sheet
void oled_init()
 {
    write_c(0x10ae); // display off
    write_c(0x10a1); //segment remap
    write_c(0x10da); //common pads hardware: alternative
    write_c(0x1012);
    write_c(0x10c8); //common output scan direction:com63~com0
    write_c(0x10a8); //multiplex ration mode:63
    write_c(0x103f);
    write_c(0x10d5); //display divide ratio/osc. freq. mode
    write_c(0x1080);
    write_c(0x1081); //contrast control
    write_c(0x1050);
    write_c(0x10d9); //set pre-charge period
    write_c(0x1021);
    write_c(0x1020); //Set Memory Addressing Mode
    write_c(0x1002);
    write_c(0x10db); //VCOM deselect level mode
    write_c(0x1030);
    write_c(0x10ad); //master configuration
    write_c(0x1000);
    write_c(0x10a4); //out follows RAM content
    write_c(0x10a6); //set normal display
    write_c(0x10af); // display on 
    
    EXTERNAL_MEMORY->OLED_COMMAND[0xaf] = 0x10af;
 }