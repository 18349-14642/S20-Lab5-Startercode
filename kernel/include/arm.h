/** @file arm.h
 *
 *  @brief  Assembly wrappers for arm instructions.
 *
 *  @date   March 27, 2019
 *
 *  @author Ronit Banerjee <ronitb@andrew.cmu.edu>
 */
#ifndef _ARM_H_
#define _ARM_H_

#include <stdint.h>

void enable_interrupts(void);
void disable_interrupts(void);
void breakpoint(void);
void wait_for_interrupt(void);

#endif /* _ARM_H_ */
