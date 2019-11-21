import argparse
import os
import spidev
import threading
import time
import random

# SPI Configuration
BUS = 0
DEVICE = 1
BITS_PER_WORD = 8
MAX_SPI_SPEED_HZ = 1000000
CPOL = (1 << 1)
CPHA = (1 << 0)

# The position of the wheel is encoded in 1 byte
# 1 byte = 256 unique steps
TICKS_PER_ROTATION = 256

# Default PID constants
K_P = 1
K_D = 0
BIAS = 0
MAX_MOTOR_SPEED = 90
MIN_MOTOR_SPEED = 0

target = 0
old_error = 0

# Initialize SPI on the RPi
def spi_init():
    spi = spidev.SpiDev()
    spi.open(BUS, DEVICE)
    spi.max_speed_hz = MAX_SPI_SPEED_HZ
    spi.mode = CPOL | CPHA
    spi.bits_per_word = BITS_PER_WORD
    return spi

# Calculate the required speed and direction based on the current position
def do_pid(position, k_p, k_d, bias):
    global old_error

    # Logic to find shortest path to target position
    error = target - position
    if (error > (TICKS_PER_ROTATION / 2)):
        error = error - TICKS_PER_ROTATION
    elif (error < -(TICKS_PER_ROTATION / 2)):
        error = error + TICKS_PER_ROTATION

    # Determine direction based on error. 
    # TODO: You may need to flip these based on the direction your motor spins!
    if (error < 0):
        direction = 1
    else:
        direction = 0

    speed = k_p * abs(error) - k_d * abs(error - old_error) + bias
    speed = min(MAX_MOTOR_SPEED, speed)
    speed = max(speed, MIN_MOTOR_SPEED)

    # TODO: Feel free to add/change additional logic, like setting a max/min 
    # speed, using thresholds on error, adding the I term, etc. 
    # - Setting a max speed can be useful to prevent browning out if the power
    #   supply cannot supply enough current
    # - Setting a min speed can help the motor overcome friction near the target

    old_error = error

    return (int(speed), int(direction))

def get_target_thread():
    global target
    try:
        while (True):
            print("Input new target: ", end='')
            try:
                target = int(input()) & 0xFF;
            except ValueError:
                print("Error: Not an integer")

    except KeyboardInterrupt:
        return

def main(k_p, k_d, bias):
    spi = spi_init()
    threading.Thread(target=get_target_thread,args=()).start()
    
    speed = 0
    direction = 0
    try:
        while True:
            # TODO:Use spi.xfer2 to send the message to the STM32,
            # and receive the position of the motor as a reply.
            
            # TODO: Update the speed and direction based on the new position
            # using the do_pid function

            time.sleep(0.01)

    except KeyboardInterrupt:
        return

def get_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('-kp', '--k_proportional', help="Proportional Constant (Tune me!)", type=float, default=K_P)
    parser.add_argument('-kd', '--k_derivative', help="Derivative Constant (Tune me!)",  type=float, default=K_D)
    parser.add_argument('-b', '--bias', help="Bias Constant (Tune me!)",  type=float, default=BIAS)

    args = parser.parse_args()
    return args

if __name__ == '__main__':
    start_time = time.time()

    args = get_args()
    main(args.k_proportional, args.k_derivative, args.bias)

    print("\nTotal time taken: " + str(time.time() - start_time) + " seconds")
    os._exit(0)