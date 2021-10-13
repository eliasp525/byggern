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
    printf("Hello World\n\r");

    // PIOA->PIO_PA19 = 1;
    // PIOA->PIO_PA20 = 1;

    while (1)
    {   
        
    }
    
}