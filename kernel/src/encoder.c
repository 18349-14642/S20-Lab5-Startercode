#include <encoder.h>
#include <exti.h>
#include <gpio.h>
#include <unistd.h>
#include <nvic.h>
#include <printk.h>
#include <arm.h>
#include <spi.h>

typedef enum {S00 = 0, S10 = 0x2, S11 = 0x3, S01 = 0x1} encoder_state;

/**
 * @brief Initialize the encoder
 * This only supports one encoder at a time
 */
void encoder_init() {
  return;
}

/**
 * @brief Stop the encoder
 * This only supports one encoder at a time
 */
void encoder_stop() {
  return;
}

/**
 * @brief Returns the current position of the encoder
 */
uint8_t encoder_read() {
  return 0;
}

/**
 * @brief Handle the IRQ for the encoder
 * Calculate the position.
 */
void encoder_irq_handler() {
  return;
}
