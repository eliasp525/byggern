#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "PWM.h"
#include "adc.h"
#include "bit_operations.h"
#include "constants.h"
#include "external_memory.h"
#include "input.h"
#include "oled.h"
#include "sram_test.h"
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"
#include "mcp2515_registers.h"

#include <util/delay.h> //this must be after constants.h

uint8_t interrupt_flag = 0;

ISR(INT1_vect){
    interrupt_flag = 1;
}

int main() {
    DDRA = 0;
    USART_init(MYUBRR);
    interrupt_init();

    fdevopen(USART_transmit, USART_receive);

    config_external_memory();

    PWM_init();

    int8_t bias[2] = {0,0};  // X is index 0, Y is index 1
    int8_t position[2] = {0,0};
    uint8_t buttons[2] = {0,0};
    uint8_t slider[2] = {0,0};

    calibrate_joystick_bias(bias);

    int0_flag = 0;

    oled_init();

    oled_reset();
    //led_goto_position(32, 1);

    oled_draw_star();

    // printo("Hello world!", 0);
    // oled_goto_position(0, 3);
    // printo("Hello world!", 1);

    _delay_ms(1500);

    //oled_reset();

    char* menu_elements[TOTAL_PAGES];
    menu_elements[0] = "Option 1";
    menu_elements[1] = "Option 2";
    menu_elements[2] = "Option 3";
    menu_elements[3] = "Exit";
    menu_elements[4] = "";
    menu_elements[5] = "";
    menu_elements[6] = "";
    menu_elements[7] = "===MAIN MENU====";

    //run_menu(bias, menu_elements);

    mcp_init();
    char rec_data[9] = "";
    can_msg receive_message = {.id = 1, .data = &rec_data , .len = 8};

    can_msg send_message;
    uint8_t tx_flag = 0;

    while (1) {

        

        // mcp_write(0b00110110, 'h');
        // printf("mcp register TXB0D0: %d\n\r", mcp_read(0b00110110));
        // printf("mcp register TXB0D0: %c\n\r", mcp_read(0b00110110));
        // printf("mcp status-register : %c\n\r", mcp_read_status());
        
        
        calculate_x_y(position, bias);

        if (int0_flag){
            int0_flag = 0;
            send_message = {.id = 42, .data = &position, .len = 2};
            //printf("sending msg \r\n");
        }
        else{
            send_message = {.id = 69, .data = &position, .len = 2};
        }
           

        can_send_msg(send_message);
        tx_flag = 1;


        //send_joystick_x_y(&position);
        //printf("Sending message: %s\r\n", message.data);
             
        //read_touch_buttons(buttons);
        //printf("\r\nButtons: L: %d,   R: %d", buttons[0], buttons[1]);
        // printf("Bias -  X: %d, Y: %d", bias[0], bias[1]);
        printf("MAIN X: %d, Y: %d \r\n", position[0], position[1]);
        // printf("joystick direction : %d \r\n", calculate_direction(bias));
        // printf("Slider_left: %d \r\n", read_adc_channel(2));
        // printf("Slider_right: %d \r\n", read_adc_channel(3));
        
        while (interrupt_flag == 1 or tx_flag == 1){
            
            uint8_t int_val = mcp_read_interrupt();
            // printf("Value interrupt: %d\r\n", int_val);
            switch(int_val){

                case INT_TX0:
                    tx_flag = 0;
                    // printf("interrupt on TX0\r\n");
                    mcp_clear_interrupt_bit(MCP_TX0IF);
                    break;

                case INT_TX1:
                    printf("interrupt on TX1\r\n");
                    mcp_clear_interrupt_bit(MCP_TX1IF);
                    break;

                case INT_TX2:
                    printf("interrupt on TX2\r\n");
                    mcp_clear_interrupt_bit(MCP_TX2IF);
                    break;

                case INT_RX0:
                    printf("interrupt on RX0\r\n");
                    can_recieve_msg(&receive_message, 0);
                    // printf("Received message: x %d y %d \r\n", receive_message.data[0], receive_message.data[1]);
                    mcp_clear_interrupt_bit(MCP_RX0IF);
                    break;

                case INT_RX1:
                    printf("interrupt on RX1\r\n");
                    can_recieve_msg(&receive_message, 1);
                    printf("Received message: %s \r\n", receive_message.data);
                    mcp_clear_interrupt_bit(MCP_RX1IF);
                    break;

                default:
                    printf("ERROR: Undefined interrupt\r\n");
                    mcp_bit_modify(MCP_CANINTF, 0xff, 0);
                    break;
            }

            if(mcp_read(MCP_CANINTF) == 0){interrupt_flag = 0;}
        }
        _delay_ms(10);
    }

    return 0;
}