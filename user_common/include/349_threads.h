/** @file 349_threads.h
 *
 *  @brief  Custom syscalls to support real-time threading in 18-349.
 *
 *  @author Ian Hartwig <ihartwig@andrew.cmu.edu>
 *  @author Ronit Banerjee <ronitb@andrew.cmu.edu>
 */

#ifndef _SYSCALL_THREAD_H_
#define _SYSCALL_THREAD_H_

#include <stdint.h>

typedef enum { PER_THREAD = 1, KERNEL_ONLY = 0 } memory_protection_t;

/**
 * @brief      Initialize the thread library
 *
 *             A user program must call this initializer before attempting to
 *             create any threads or start the scheduler.
 *
 * @param      max_threads        max number of threads created
 * @param      stack_size         Declares the size in words of all the stacks
 *                                for subsequent calls to thread create.
 * @param      idle_func          Pointer to a thread function to run when no
 *                                other threads are runnable, if arg is NULL,
 *                                then kernel will supply default idle thread.
 * @param      memory_protection  If KERNEL_ONLY, then kernel will be
 *                                protected if PER_THREAD, perthread mem
 *                                protection in addition to kernel protection.
 * @param      max_mutexes        max number of mutexes created
 *
 * @return     0 on success or -1 on failure
 */
int thread_init( uint32_t max_threads,
                 uint32_t stack_size,
                 void ( *idle_func )( void ),
                 memory_protection_t memory_protection,
                 uint32_t max_mutexes );

/**
 * @brief      Create a new thread running the given function
 *
 * @param      fn     Pointer to the function to run in the new thread.
 * @param      prio   Priority of this thread. Lower number are higher
 *                    priority.
 * @param      C      Real time execution time (ms).
 * @param      T      Real time task period (ms).
 * @param      vargp  Pointer to an argument.
 *
 * @return     0 on success or -1 on failure. Runs ub test for new task set
 *             will fail if over ub test.
 */
int thread_create( void ( *fn )( void *vargp ),
                   uint32_t prio,
                   uint32_t C,
                   uint32_t T,
                   void *vargp );

/**
 * @brief      Allow the kernel to start running the added task set.
 *
 *             This function should enable IRQs and thus enable your
 *             scheduler. The kernel will test that a task set with this new
 *             task is scheduleable before running and may return an error if
 *             this is not the case.
 *
 * @param[in]  freq  The frequency
 *
 * @return     0 on success or -1 on failure
 */
int scheduler_start( uint32_t frequency );

/**
 * @brief      Get the current time.
 *
 * @return     The time in ticks.
 */
uint32_t get_time( void );

/**
 * @brief      Get the effective priority of the current running thread
 *
 * @return     The thread's effective priority
 */
uint32_t get_priority( void );

/**
 * @brief      Gets the total elapsed time for the thread (since its first
 *             ever period.)
 *
 * @return     The time in ticks.
 */
uint32_t thread_time( void );

/**
 * @brief      Waits efficiently by descheduling thread.
 */
void wait_until_next_period( void );

/**
 * @brief      Type definition for mutex, opaque to user
 */
typedef struct {
  char unused;
} mutex_t;

/**
 * @brief      Initialize a mutex
 *
 *             A user program calls this function to obtain a mutex.
 *
 * @param      max_prio  The maximum priority of a thread which could use
 *                       this mutex.
 *
 * @return     A mutex handle, uniquely referring to this mutex. NULL if
 *             max_mutexes would be exceeded.
 */
mutex_t *mutex_init( uint32_t max_prio );

/**
 * @brief      Lock a mutex
 *
 *             This function will not return until the current thread has
 *             obtained the mutex.
 *
 * @param      mutex  The mutex to act on.
 */
void mutex_lock( mutex_t *mutex );

/**
 * @brief      Unlock a mutex
 *
 * @param      mutex  The mutex to act on.
 */
void mutex_unlock( mutex_t *mutex );

#endif /* _SYSCALL_THREAD_H_ */
