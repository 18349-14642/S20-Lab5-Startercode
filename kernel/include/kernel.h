/** @brief Period for the timer.*/
#define TIMER_PERIOD 12000
/** @brief  increment for system tic.*/
#define SYSTEM_TICK 1
/** @brief Return code to return to user mode with user stack.*/
#define RETURN_TO_USER_PSP 0xFFFFFFFD

#ifdef DEBUG
#define ASSERT(X) if(!X) {__asm volatile("bkpt");} else do {} while(0) 
#define DEBUG_PRINT(...) printk(__VA_ARGS__)
#else
#define ASSERT(...) do {} while(0)
#define DEBUG_PRINT(...) do {} while(0)
#endif /* DEBUG */