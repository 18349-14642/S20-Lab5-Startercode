// Kevin DeVincentis
#ifndef _SPI_H_
#define _SPI_H_

/** @brief SPI register map. */
struct spi_reg_map {
  volatile uint32_t cr1; /**< cr 1 */
  volatile uint32_t cr2; /**< cr 2 */
  volatile uint32_t sr; /**< sr */
  volatile uint32_t dr; /**< dr */
  volatile uint32_t crcpr; /**< crcpr */
  volatile uint32_t rxcrcr; /**< rxcrcr */
  volatile uint32_t txcrcr; /**< txcrcr */
  volatile uint32_t i2scfgr; /**< i2scfgr */
  volatile uint32_t i2spr; /**< i2spr */
};

#define SPI1_BASE (struct spi_reg_map *) 0x40013000

void spi_slave_init();
void spi_slave_stop();
void spi_slave_irq_handler();
void spi_slave_write(uint8_t data);


#endif /* _SPI_H_ */
