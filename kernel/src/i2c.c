/**
 * @file i2c.c
 *
 * @brief      
 *
 * @date       
 *
 * @author     
 */

#include <gpio.h>
#include <i2c.h>
#include <unistd.h>
#include <rcc.h>

#define UNUSED __attribute__((unused))

void i2c_master_init(UNUSED uint16_t clk){

}

int i2c_master_start(){
  return -1;
}

int i2c_master_stop(){
  return -1;
}

int i2c_master_write(UNUSED uint8_t *buf, UNUSED uint16_t len, UNUSED uint8_t slave_addr){
  return -1;
}

int i2c_master_read(UNUSED uint8_t *buf, UNUSED uint16_t len, UNUSED uint8_t slave_addr){
  return -1;
}
