#include <motor_driver.h>
#include <unistd.h>
#include <gpio.h>
#include <pwm.h>
#include <encoder.h>

#define PWM_PERIOD 4000

#define MAX_DUTY_CYCLE 100

static gpio_port PORT_A;
static gpio_port PORT_B;
static gpio_port PORT_PWM;

static uint32_t CHANNEL_A;
static uint32_t CHANNEL_B;
static uint32_t CHANNEL_PWM;

static uint32_t TIMER;
static uint32_t TIMER_CHANNEL;

void motor_init(gpio_port port_a, gpio_port port_b, gpio_port port_pwm, uint32_t channel_a, uint32_t channel_b, uint32_t channel_pwm, uint32_t timer, uint32_t timer_channel, uint32_t alt_timer)
{
  PORT_A = port_a;
  PORT_B = port_b;
  PORT_PWM = port_pwm;
  CHANNEL_A = channel_a;
  CHANNEL_B = channel_b;
  CHANNEL_PWM = channel_pwm;

  TIMER = timer;
  TIMER_CHANNEL = timer_channel;

  gpio_init(PORT_A, CHANNEL_A, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_HIGH, PUPD_PULL_DOWN, ALT0);
  gpio_init(PORT_B, CHANNEL_B, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_HIGH, PUPD_PULL_DOWN, ALT0);
  gpio_init(PORT_PWM, CHANNEL_PWM, MODE_ALT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_VERY_HIGH, PUPD_PULL_DOWN, alt_timer);
  encoder_init();
  start_pwm_timer(PWM_PERIOD, 0, TIMER, TIMER_CHANNEL);
}

uint8_t motor_position() {
  return encoder_read();
}

void motor_set_dir(uint32_t duty_cycle, uint32_t direction) {
  if (duty_cycle > MAX_DUTY_CYCLE) duty_cycle = MAX_DUTY_CYCLE;

  switch (direction) {
    case FREE:
      duty_cycle = 0;
    break;

    case FORWARD:
      gpio_set(PORT_A, CHANNEL_A);
      gpio_clr(PORT_B, CHANNEL_B);
    break;

    case BACKWARD:
      gpio_clr(PORT_A, CHANNEL_A);
      gpio_set(PORT_B, CHANNEL_B);
    break;

    case STOP:
      gpio_set(PORT_A, CHANNEL_A);
      gpio_set(PORT_B, CHANNEL_B);
    break;

    default:
      gpio_clr(PORT_A, CHANNEL_A);
      gpio_clr(PORT_B, CHANNEL_B);

  }

  change_duty_cycle(TIMER, TIMER_CHANNEL, duty_cycle * PWM_PERIOD / MAX_DUTY_CYCLE);
}
