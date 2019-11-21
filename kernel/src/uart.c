/**
 * @file 
 *
 * @brief      
 *
 * @date       
 *
 * @author     
 */

#include <unistd.h>
#include <rcc.h>
#include <uart.h>
#include <uart_polling.h>
#include <nvic.h>

#define UNUSED __attribute__((unused))

void uart_init(UNUSED int baud){

}

int uart_put_byte(UNUSED char c){
  return -1;
}

int uart_get_byte(UNUSED char *c){
  return -1;
}

void uart_irq_handler(){

}

void uart_flush(){

}