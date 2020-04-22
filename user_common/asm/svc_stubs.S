/**
 * @file   swi_stubs.S
 *
 * @brief  Stub functions for newlib and 349libc syscalls
 *
 * @date
 * @author
 */

.cpu cortex-m4
.syntax unified
.section .swi_stub
.thumb

#include "../../kernel/include/svc_num.h"

.global _sbrk
_sbrk:
  bkpt

.global _write
_write:
  bkpt

.global _close
_close:
  bkpt

.global _fstat
_fstat:
  bkpt

.global _isatty
_isatty:
  bkpt

.global _lseek
_lseek:
  bkpt

.global _read
_read:
  bkpt

.global _exit
_exit:
  bkpt

.type thread_init, %function
.global thread_init
thread_init:
  bkpt

.type thread_create, %function
.global thread_create
thread_create:
  bkpt

.type thread_kill, %function
.global thread_kill
thread_kill:
  bkpt

.type scheduler_start, %function
.global scheduler_start
scheduler_start:
  bkpt

.type mutex_init, %function
.global mutex_init
mutex_init:
  bkpt

.type mutex_lock, %function
.global mutex_lock
mutex_lock:
  bkpt

.type mutex_unlock, %function
.global mutex_unlock
mutex_unlock:
  bkpt

.type wait_until_next_period, %function
.global wait_until_next_period
wait_until_next_period:
  bkpt

.global get_time
get_time:
  bkpt

.global get_priority
get_priority:
  bkpt

.global thread_time
thread_time:
  bkpt

.global servo_enable
servo_enable:
  bkpt

.global servo_set
servo_set:
  bkpt

/* The following stubs are not required to be implemented */

.global _start
_start:
  bkpt

.global _kill
_kill:
  bkpt
  
.global _gettimeofday
_gettimeofday:
  bkpt

.global _times
_times:
  bkpt

.global _getpid
_getpid:
  bkpt

.thumb_func
.global idle_default
idle_default:
  wfi
  b idle_default
 
 
 
