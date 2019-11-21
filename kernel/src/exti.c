#include <exti.h>
#include <gpio.h>
#include <rcc.h>
#include <printk.h>

/** @brief EXTI register map. */
struct exti {
  volatile uint32_t imr;   /**< 00 Interrupt Mask Register */
  volatile uint32_t emr;   /**< 04 Event Mask Register */
  volatile uint32_t rtsr;  /**< 08 Rising trigger Selection */
  volatile uint32_t ftsr;  /**< 0C Falling trigger Selection */
  volatile uint32_t swier; /**< 10 Software Interrupt Event Register */
  volatile uint32_t pr;    /**< 14 Pending Register */
};

/** @brief System Config register map. */
struct syscfg {
  volatile uint32_t memrmp; /**< 00 Memory Remap */
  volatile uint32_t pmc; /**< 04 Peripheral mode configuration */
  volatile uint32_t exti[4]; /**< 08-14 External interrupt configuration */
  volatile uint32_t cmpcr; /**< 20 Compensation cell control */
};

#define EXTI_BASE (struct exti *) 0x40013C00
#define SYSCFG_BASE (struct syscfg *) 0x40013800

#define BITS_PER_EXTI 4

#define RCC_APB2_SYSCFG_EN (1 << 14)


void enable_exti(gpio_port port, uint32_t channel, uint32_t edge) {
  struct exti *exti = EXTI_BASE;
  struct syscfg *syscfg = SYSCFG_BASE;
  struct rcc_reg_map *rcc = RCC_BASE;

  rcc->apb2_enr |= RCC_APB2_SYSCFG_EN;

  exti->imr |= (0x1 << channel);

  if (edge == RISING_EDGE) {
    exti->rtsr |= (0x1 << channel);
  }
  else if (edge == FALLING_EDGE) {
    exti->ftsr |= (0x1 << channel);
  }
  else if (edge == RISING_FALLING_EDGE) {
    exti->rtsr |= (0x1 << channel);
    exti->ftsr |= (0x1 << channel);
  }

  uint32_t shift = channel % 4;
  uint32_t reg = (uint32_t)channel/4;
  syscfg->exti[reg] |= (port << (shift * BITS_PER_EXTI));
}

void disable_exti(uint32_t channel) {
  struct exti *exti = EXTI_BASE;

  exti->imr &= ~(0x1 << channel);
}

void exti_clear_pending_bit(uint32_t channel) {
  struct exti *exti = EXTI_BASE;

  exti->pr |= (0x1 << channel);
}
