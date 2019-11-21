#ifndef _PWM_H_
#define _PWM_H_


#include <unistd.h>
#include <gpio.h>

uint8_t IS_COMP;

/*
 * Starts the timer based pwm
 *
 * @param period     - The period of the PWM
 * @param duty_cycle - The starting duty cycle of the PWM signal
 * @param timer      - The timer controlling the PWM
 * @param channel    - The timer channel controlling the PWM
 */
void start_pwm_timer(uint32_t period, uint32_t duty_cycle, uint32_t timer, uint32_t channel);

/*
 * Stops the timer based pwm
 *
 * @param timer      - The timer controlling the PWM
 * @param channel    - The timer channel controlling the PWM
 */
void disable_pwm_timer(uint32_t timer, uint32_t channel);

/*
 * Changes the duty cycle of the PWM signal
 *
 * @param duty_cycle - The new duty cycle of the PWM signal
 * @param timer      - The timer controlling the PWM
 * @param channel    - The timer channel controlling the PWM
 */
void change_duty_cycle(uint32_t timer, uint32_t channel, uint32_t duty_cycle);

#endif /* _PWM_H_ */
