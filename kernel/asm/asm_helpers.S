.cpu cortex-m4
.syntax unified
.thumb

.section .text

.thumb_func
.global enter_user_mode
enter_user_mode:
  bkpt


.thumb_func
.global context_swap_asm
context_swap_asm:
  bx lr
