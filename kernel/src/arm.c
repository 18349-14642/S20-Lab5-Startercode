#include <arm.h>
#include <stdint.h>

/* @brief Refister to enable/disable fpu */
#define CPACR ((volatile uint32_t *) 0xE000ED88)
/* @brief FPU control data */
#define FPCCR ((volatile uint32_t *) 0xE000EF34)
/* @brief Hold the address of the unpopulated floating point
 * register space in stackframe*/
#define FPCAR ((volatile uint32_t *) 0xE000EF38)
/* @brief  Default values for the floating point status
 * control data (FPCCR) */
#define FPDSCR ((volatile uint32_t *) 0xE000EF3C)
/* @brief  Read-only information about what VFP instruction features are
 * implemented */
#define MVFR0 ((volatile uint32_t *) 0xE000EF40)
/* @brief  Read-only information about what VFP instruction features are
 * implemented */
#define MVFR1 ((volatile uint32_t *) 0xE000EF44)

void enable_interrupts(void){
  __asm volatile("CPSIE f");
}

void disable_interrupts(void){
  __asm volatile("CPSID f");
}

void breakpoint(void){
  __asm volatile("bkpt");
}

void wait_for_interrupt(void){
  __asm volatile("wfi");
}
