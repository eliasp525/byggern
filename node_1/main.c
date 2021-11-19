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
#include "menu.h"

#include <util/delay.h> //this must be included after constants.h

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
    char rec_data[9] = "";
    can_msg receive_message = {.id = 1, .data = &rec_data , .len = 8};
    int0_flag = 0;
    
    
    calibrate_joystick_bias(bias);
    

    oled_init();
    oled_reset();
    oled_draw_star();

    mcp_init();
    //init_highscore();
    
    _delay_ms(1500);

    
    uint8_t player;
    uint8_t score;
    uint8_t game_over;
    GameState game_state = MENU;

    
    while (game_state != EXIT){
        game_over = 0;
        score = 0;
        game_state = menu(bias, &player);
        update_score_screen(score);

        printf("player: %d \r\n", player);

        if (game_state == PLAY_TIMED || game_state == PLAY_FREE){
            can_msg game_message = {.id = 30, .data = &game_state, .len = 1};
            can_send_msg(game_message);
        }

        while (game_state != EXIT && !game_over) {

            while (interrupt_flag == 1){
                
                uint8_t int_val = mcp_read_interrupt();
                // printf("Value interrupt: %d\r\n", int_val);
                switch(int_val){

                    case INT_TX0:
                        // printf("interrupt on TX0\r\n");
                        mcp_clear_interrupt_bit(MCP_TX0IF);
                        break;

                    case INT_TX1:
                        //printf("interrupt on TX1\r\n");
                        mcp_clear_interrupt_bit(MCP_TX1IF);
                        break;

                    case INT_TX2:
                        //printf("interrupt on TX2\r\n");
                        mcp_clear_interrupt_bit(MCP_TX2IF);
                        break;

                    case INT_RX0:
                        //printf("interrupt on RX0\r\n");
                        can_recieve_msg(&receive_message, 0);
                        if (receive_message.id == 10){
                            score++;
                            update_score_screen(score);
                        }
                        mcp_clear_interrupt_bit(MCP_RX0IF);
                        break;

                    case INT_RX1:
                        //printf("interrupt on RX1\r\n");
                        can_recieve_msg(&receive_message, 1);
                        if (receive_message.id == 10){
                            score++;
                            update_score_screen(score);
                        }
                        else if (receive_message.id == 30){
                            update_high_score(player, score);
                            game_over = 1;
                        }
                        mcp_clear_interrupt_bit(MCP_RX1IF);
                        break;

                    default:
                        //printf("ERROR: Undefined interrupt\r\n");
                        mcp_bit_modify(MCP_CANINTF, 0xff, 0);
                        break;
                }

                if(mcp_read(MCP_CANINTF) == 0){interrupt_flag = 0;}
            }


            if (int0_flag){
                int0_flag = 0;
                can_msg button_message = {.id = 42, .data = &position, .len = 2};
                can_send_msg(button_message);
                //printf("sending msg HIT BALL\r\n");
                _delay_ms(10);
            }
            if (game_over){
                break;
            }

            calculate_x_y(position, bias);
            send_joystick_x_y(&position);

            _delay_ms(20);
        }

        oled_draw_star();
        _delay_ms(2500);
    }

    
    return 0;
}