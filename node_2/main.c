#include <stdio.h>
#include <stdarg.h>
#include "uart.h"
#include "printf-stdarg.h"

#include "sam.h"


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    configure_uart();

    PMC->PMC_PCER0 = PMC_PCER0_PID11;
    PIOA->PIO_PER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
    PIOA->PIO_OER = (PIO_PA19 | PIO_PA20 | PIO_PA14);
    
    PIOA->PIO_SODR = PIO_PA19;
    PIOA->PIO_SODR = PIO_PA20;
    PIOA->PIO_SODR = PIO_PA14;

    while(1){
        printf("Hello World\n\r");
    }
    
}