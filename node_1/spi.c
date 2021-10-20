#include "spi.h"

//pulled from the atmega docs and modified to our needs
void spi_master_init(){
/* Set !SS, MOSI and SCK output, all others input */
DDRB = (1 << DDB4)|(1<<DDB5)|(1<<DDB7);
/* Enable SPI, Master, set clock rate default fck/4 */
SPCR = (1<<SPE)|(1<<MSTR);
}

//pulled from the atmega docs and modified to our needs
char spi_master_transceive(char cData){
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)));
return SPDR;
}

void end_transmission(){
    set_bit(PORTB, PB4);
}

void start_transmission(){
    clear_bit(PORTB, PB4);
}


