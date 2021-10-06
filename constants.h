#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define EXTERNAL_MEMORY_LOCATION 0x1000

#define EXTERNAL_MEMORY ((EXTERNAL_MEMORY_MAP*)EXTERNAL_MEMORY_LOCATION)

#define F_CPU 4915200

#define SINGLE_CHANNEL_ADDRESS 0b10000000

#define MAX_AMP 255
#define MIN_AMP 0
#define NO_AMP 128
#define Y_DIRECTION 0
#define X_DIRECTION 1

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define TOTAL_PAGES 8
#define MENU_HEIGHT 8

#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#endif