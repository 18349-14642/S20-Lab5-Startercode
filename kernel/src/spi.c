// Kevin DeVincentis

#include <gpio.h>
#include <printk.h>
#include <unistd.h>
#include <rcc.h>
#include <spi.h>
#include <nvic.h>
#include <motor_driver.h>

#define SPI1_SS 8
#define SPI1_NSS 4
#define SPI1_SCK 3
#define SPI1_MISO 4
#define SPI1_MOSI 5
#define SPI2_SCK 13
#define SPI2_MISO 14
#define SPI2_MOSI 15

#define SPI_BR_1_MHZ (1 << 4)
#define SPI_MASTER_MODE (1 << 2)
#define SPI_CPOL_HIGH (1 << 1)
#define SPI_CPHA_HIGH (1 << 0)
#define SPI_SSM (1 << 9)
#define SPI_SSI (1 << 8)

#define SPI_SSOE_EN (1 << 2)
#define SPI_EN (1 << 6)

#define SPI_BSY (1 << 7)
#define SPI_TX_EMPTY (1 << 1)
#define SPI_RX_NOT_EMPTY (1 << 0)

#define SPI_TXEIE (1 << 7)
#define SPI_RXNEIE (1 << 6)

#define SPI_IRQ 35

#define SPEED_MASK 0x7F
#define DIR_MASK 0x80

#define RCC_APB2_SPI1_EN (1 << 12)

/**
 * @brief Initializes SPI1 on the STM32F4
 */
void spi_slave_init(){
  gpio_init(GPIO_B, SPI1_SCK, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_HIGH, PUPD_NONE, ALT5);
  gpio_init(GPIO_B, SPI1_MISO, MODE_ALT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_HIGH, PUPD_NONE, ALT5);
  gpio_init(GPIO_B, SPI1_MOSI, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_HIGH, PUPD_NONE, ALT5);

  // Enable NVIC interrupt for spi1 (IRQ35)
  nvic_irq(SPI_IRQ, IRQ_ENABLE);

  /* Enable Alternate Function clock and I2C1 in RCC regs */
  struct rcc_reg_map *rcc = RCC_BASE;
  rcc->apb2_enr |= RCC_APB2_SPI1_EN;

  struct spi_reg_map *spi = SPI1_BASE;
  // Set baud rate, slave mode, and clock polarity and phase
  // Software NSS, SSM = 1
  spi->cr1 = SPI_BR_1_MHZ | SPI_CPHA_HIGH | SPI_CPOL_HIGH | SPI_SSM;

  // Turn on RX interrupts
  spi->cr2 = SPI_TXEIE | SPI_RXNEIE;
  spi->cr1 |= SPI_EN; // Turn on SPI

}

/**
 * @brief Stops SPI1 on the STM32F4
 */
void spi_slave_stop(){
  struct spi_reg_map *spi = SPI1_BASE;

  spi->cr1 &= ~SPI_EN; // Turn off SPI

}

/**
 * @brief Writes data into the SPI data register.
 * This data will be transfered in the next SPI transfer
 *
 * @param position  - the data to send over SPI to the master
 */
void spi_slave_write(uint8_t data) {
  struct spi_reg_map *spi = SPI1_BASE;

  spi->dr = data;
}

/**
 * @brief Read data from the SPI data register.
 */
uint8_t spi_slave_read() {
  struct spi_reg_map *spi = SPI1_BASE;

  uint8_t data = spi->dr;
  return data;
}

/**
 * @brief SPI IRQ Handler
 * This must be added to the table in /asm/boot.S for spi to work properly
 */
void spi_slave_irq_handler(){
  return;

}