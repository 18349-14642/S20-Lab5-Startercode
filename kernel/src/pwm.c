#include <pwm.h>
#include <unistd.h>
#include <rcc.h>
#include <printk.h>

/** @brief TIM1 register map. */
struct tim1 {
  volatile uint32_t cr1; /**< 00 Control Register 1 */
  volatile uint32_t cr2; /**<04 Control Register 2 */
  volatile uint32_t smcr; /**< 08 Slave Mode Control */
  volatile uint32_t dier; /**< 0C DMA/Interrupt Enable */
  volatile uint32_t sr; /**< 10 Status Register */
  volatile uint32_t egr; /**< 14 Event Generation */
  volatile uint32_t ccmr[2]; /**< 18-1C Capture/Compare Mode */
  volatile uint32_t ccer; /**< 20 Capture/Compare Enable */
  volatile uint32_t cnt; /**< 24 Counter Register */
  volatile uint32_t psc; /**< 28 Prescaler Register */
  volatile uint32_t arr; /**< 2C Auto-Reload Register */
  volatile uint32_t rcr; /**< 30 Repetition Counter Register */
  volatile uint32_t ccr[4]; /**< 34-40 Capture/Compare */
  volatile uint32_t bdtr; /**< 44 Break and Dead-Time Register */
  volatile uint32_t dcr; /**< 48 DMA Control Register */
  volatile uint32_t dmar; /**< 4C DMA address for full transfer Register */
};

/** @brief TIM2-5 register map. */
struct tim2_5 {
  volatile uint32_t cr1; /**< 00 Control Register 1 */
  volatile uint32_t cr2; /**< 04 Control Register 2 */
  volatile uint32_t smcr; /**< 08 Slave Mode Control */
  volatile uint32_t dier; /**< 0C DMA/Interrupt Enable */
  volatile uint32_t sr; /**< 10 Status Register */
  volatile uint32_t egr; /**< 14 Event Generation */
  volatile uint32_t ccmr[2]; /**< 18-1C Capture/Compare Mode */
  volatile uint32_t ccer; /**< 20 Capture/Compare Enable */
  volatile uint32_t cnt; /**< 24 Counter Register */
  volatile uint32_t psc; /**< 28 Prescaler Register */
  volatile uint32_t arr; /**< 2C Auto-Reload Register */
  volatile uint32_t reserved_1; /**< 30 */
  volatile uint32_t ccr[4]; /**< 34-40 Capture/Compare */
  volatile uint32_t reserved_2; /**< 44 */
  volatile uint32_t dcr; /**< 48 DMA Control Register */
  volatile uint32_t dmar; /**< 4C DMA address for full transfer Register */
  volatile uint32_t or; /**< 50 Option Register */
};

/** @brief Base address of TIM1 */
#define TIM1_BASE (struct tim1 *) 0x40010000

const uint32_t tim_en[] = {0x0, 0x1, 0x1, 0x2, 0x4, 0x8};


struct tim2_5* const timer_base[] = {(void *)0x0,  // N/A
                                     (void *)0x0, // N/A
                                     (void *)0x40000000, // TIMER 2
                                     (void *)0x40000400, // TIMER 3
                                     (void *)0x40000800, // TIMER 4
                                     (void *)0x40000C00}; // TIMER 5

#define CR1_AUTO_RELOAD_EN (0x1 << 7)                                  
#define CR1_COUNTER_EN (0x1)                              
#define PWM_MODE_1 (0x6 << 4)
#define CCRM_PRELOAD_EN (0x1 << 3)
#define CCER_EN (0x1)
#define BDTR_MOE_EN (0x1 << 15)
#define BDTR_OSSI_EN (0x1 << 10)
#define EGR_UG (0x1)

void pwm_tim1 (uint32_t period, uint32_t duty_cycle, uint32_t timer, uint32_t channel) {
  struct rcc_reg_map *rcc = RCC_BASE;
  rcc->apb2_enr |= tim_en[timer];
  struct tim1 *tim = TIM1_BASE;

  // Edge aligned mode, upcount mode

  uint32_t ccmr_reg = (uint32_t)(channel-1) / 2;
  uint32_t ccrm_shift = (channel-1) % 2;

  tim->ccmr[ccmr_reg] |= (PWM_MODE_1 | CCRM_PRELOAD_EN) << (8*ccrm_shift);

  // Auto-Reload register (period)
  tim->arr = period;

  // Capture/Compare register (duty cycle)
  tim->ccr[channel-1] = duty_cycle;

  tim->cr1 |= CR1_AUTO_RELOAD_EN | CR1_COUNTER_EN;
  // Set the UG bit to update all registers
  tim->egr |= EGR_UG;

  // Enable output
  tim->bdtr |= BDTR_MOE_EN;

  if (IS_COMP)
    tim->ccer = CCER_EN << (((channel-1)*4) + 2);
  else
    tim->ccer = CCER_EN << ((channel-1)*4);

}

void pwm_tim2_5(uint32_t period, uint32_t duty_cycle, uint32_t timer, uint32_t channel) {
  struct rcc_reg_map *rcc = RCC_BASE;
  rcc->apb1_enr |= tim_en[timer];
  struct tim2_5 *tim = timer_base[timer];

  // Edge aligned mode, upcount mode
  tim->cr1 = CR1_AUTO_RELOAD_EN | CR1_COUNTER_EN;

  uint32_t ccmr_reg = (uint32_t)(channel-1) / 2;
  uint32_t ccrm_shift = (channel-1) % 2;
  tim->ccmr[ccmr_reg] |= (PWM_MODE_1 | CCRM_PRELOAD_EN) << (8*ccrm_shift);


  // Auto-Reload register (period)
  tim->arr = period;

  // Capture/Compare register (duty cycle)
  tim->ccr[channel-1] = duty_cycle;

  // Set the UG bit to update all registers
  tim->egr |= EGR_UG;
  // Enable output
  tim->ccer |= CCER_EN << ((channel-1)*4);
}

void start_pwm_timer(uint32_t period, uint32_t duty_cycle, uint32_t timer, uint32_t channel) {
  if (timer > 5 || channel < 1 || channel > 4) return;

  if (timer == 1) {
    pwm_tim1(period, duty_cycle, timer, channel);
  }
  else {
    pwm_tim2_5(period, duty_cycle, timer, channel);
  }
}

void disable_pwm_timer(uint32_t timer, uint32_t channel) {
  struct rcc_reg_map *rcc = RCC_BASE;

  if (timer > 5 || channel < 1 || channel > 4) return;

  if (timer == 1) {
    rcc->apb2_enr &= ~tim_en[timer];
  }
  else {
    rcc->apb1_enr &= ~tim_en[timer];
  }
}

void change_tim1(uint32_t channel, uint32_t duty_cycle) {
  struct tim1 *tim = TIM1_BASE;

  tim->ccr[channel-1] = duty_cycle;
  tim->egr |= EGR_UG;
}

void change_tim2_5(uint32_t timer, uint32_t channel, uint32_t duty_cycle) {
  struct tim2_5 *tim = timer_base[timer];

  tim->ccr[channel-1] = duty_cycle;
  tim->egr |= EGR_UG;
}


void change_duty_cycle(uint32_t timer, uint32_t channel, uint32_t duty_cycle) {
  if (timer > 5 || channel < 1 || channel > 4) return;

  if (timer == 1) {
    change_tim1(channel, duty_cycle);
  }
  else {
    change_tim2_5(timer, channel, duty_cycle);
  }
}
