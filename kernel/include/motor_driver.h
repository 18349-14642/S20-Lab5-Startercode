#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <unistd.h>
#include <gpio.h>

#define FREE 0
#define FORWARD 1
#define BACKWARD 2
#define STOP 3

/*
 * Motor Driver initialization function
 * Initializes the motor driver.
 * This driver only supports one motor
 *
 * @param port_a        - GPIO port for one of the MOTOR_IN pins
 * @param port_b        - GPIO port for the other MOTOR_IN pin
 * @param port_pwm      - GPIO port for the PWM pin
 *
 * @param channel_a     - GPIO num for one of the MOTOR_IN pins
 * @param channel_b     - GPIO num for the other MOTOR_IN pin
 * @param channel_pwm   - GPIO num for the PWM pin
 *
 * @param timer         - The timer number for the PWM pin
 * @param timer_channel - The timer channel for the PWM pin
 * @param alt_timer     - The alternate function number for the timer used on the PWM pin
 *
 */
void motor_init(gpio_port port_a, gpio_port port_b, gpio_port port_pwm, uint32_t channel_a, uint32_t channel_b, uint32_t channel_pwm, uint32_t timer, uint32_t timer_channel, uint32_t alt_timer);

/*
 * Sets the direction and speed of the motor
 *
 * @param duty_cycle - Sets the duty_cycle (and thus the speed) of the PWM output. Value must be 0 - 100
 * @param direction  - must be one of FREE, FORWARD, BACKWARD, STOP
 */
void motor_set_dir(uint32_t duty_cycle, uint32_t direction);


/*
 * Returns the current position of the motor
 *
 * @return the current the position of the motor in one byte
 */
uint8_t motor_position();

#endif /* _MOTOR_DRIVER_H_ */
