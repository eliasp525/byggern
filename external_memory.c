#include "external_memory.h"
#include "bit_operations.h"
#include <avr/io.h>

void config_external_memory(){
    set_bit(MCUCR, SRE); // external memory enable
    set_bit(SFIOR, XMM2); // mask out the four MSB for using JTAG
}