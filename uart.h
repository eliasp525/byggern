
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_init( unsigned int ubrr );
void USART_transmit( unsigned char  data);
unsigned char USART_Receive();
