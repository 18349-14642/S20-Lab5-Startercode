/**
 * @file uart.c
 *
 * @brief
 *
 * @date
 * @author
 */

#include <gpio.h>
#include <unistd.h>
#include <rcc.h>
#include <uart_polling.h>

#define UNUSED __attribute__((unused))


void uart_polling_init(UNUSED int baud){

}

void uart_polling_put_byte(UNUSED char c){

}

char uart_polling_get_byte(){
  return -1;
}
