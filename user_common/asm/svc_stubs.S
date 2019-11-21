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

.global _start
_start:
  bkpt

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

.global _gettimeofday
_gettimeofday:
  bkpt

.global _times
_times:
  bkpt

.global _getpid
_getpid:
  bkpt

.global _kill
_kill:
  bkpt

.global _exit
_exit:
  bkpt

.global thread_init
thread_init:
  bkpt

.global thread_create
thread_create:
  bkpt

.global thread_kill
thread_kill:
  bkpt

.global mutex_init
mutex_init:
  bkpt

.global mutex_lock
mutex_lock:
  bkpt

.global mutex_unlock
mutex_unlock:
  bkpt

.global wait_until_next_period
wait_until_next_period:
  bkpt

.global get_time
get_time:
  bkpt

.global scheduler_start
scheduler_start:
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
