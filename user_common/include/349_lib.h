/** @file 349_lib.h.h
 *
 *  @brief  Custom functions for user programs.
 *
 *  @author Ronit Banerjee <ronitb@andrew.cmu.edu>
 */

#ifndef _THREADS_349_
#define _THREADS_349_

#include <stdio.h>
#include <stdint.h>

/**
 * @brief      Runs expr, and if it has a non-zero return value, abort program.
 *             Prints information before aborting.
 */
#define ABORT_ON_ERROR( expr , ... ) { \
  int status; status = ( expr ); if ( status ) { \
    printf( "%s: Line %d\n", __FILE__, __LINE__ ); \
    printf( #expr "\n\tfailed with status %d", status ); \
    printf( "\n" __VA_ARGS__ ); \
    exit( 1 ); \
  } \
}

#define UNUSED __attribute__((unused))

#define intrinsic __attribute__( ( always_inline ) ) static inline

/** @brief Cool LED display values */
//@{
#define RET_GOOD 0x900d
#define RET_DEAD 0xdead
#define RET_FAIL 0xfa17
#define RET_HELP_UD 0xd734
#define RET_FEED 0xfeed
#define RET_2BAD 0x2bad
#define RET_0349 0x349
//@}

/**
 * @brief      Calls wfi, which is a hint instruction. It will either put the
 *             processor to sleep or spin.
 */
intrinsic void wait_for_interrupt( void ) {
  __asm volatile( "wfi" );
}

/**
 * @brief       Pretends to do work until the given time is past.
 *              For grading.
 *
 * @param time  time at which to stop "working"
 */
void spin_until( uint32_t time );

/**
 * @brief       Pretends that the thread is doing work for ms milliseconds.
 *              For grading.
 *
 * @param ms    scheduler ticks to "work" for
 */
void spin_wait( uint32_t ms );


/**
 * @brief Prints basic status information of a thread
 *
 * @param thread_num    thread number
 * @param thread_name   name of the thread
 * @param cnt           a counter variable
 */
//@{
void print_num_status( int thread_num );
void print_num_status_cnt( int thread_num, int cnt );
void print_status( char *thread_name );
void print_status_prio( char *thread_name );
void print_status_cnt( char *thread_name, int cnt );
void print_status_prio_cnt( char *thread_name, int cnt );
//@}

/**
 * @brief           Prints out fibonacci numbers mod mod
 *
 * @param limit     stop at fib[limit]
 * @param interval  print only fib[interval * k], k integer
 * @param mod       modulo (to get the last digits only)
 *
 * @return          fib[ limit ] mod mod
 */
uint32_t print_fibs( int limit, int interval, uint32_t mod );

#undef intrinsic

#endif /* _THREADS_349_ */
