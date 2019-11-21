#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <unistd.h>
#include <gpio.h>

/*
 * Initialize the encoder
 * This only supports one encoder at a time
 */
void encoder_init();

/*
 * Stop the encoder
 * This only supports one encoder at a time
 */
void encoder_stop();

/*
 * Handle the IRQ for the encoder
 * Calculate the position.
 */
void encoder_irq_handler();

/*
 * Returns the current position of the encoder
 */
uint8_t encoder_read();


#endif /* _ENCODER_H_ */
