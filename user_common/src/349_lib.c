#include <349_threads.h>
#include <349_lib.h>

void spin_wait( uint32_t ms ) {
  uint32_t targetTime = thread_time() + ms;

  while ( thread_time() < targetTime ){
    wait_for_interrupt();
  }

  return;
}

void spin_until( uint32_t time ) {

  while ( get_time() < time ){
    wait_for_interrupt();
  }

  return;
}

void print_num_status( int thread_num ) {
  printf(
    "t=%u\tThread %d\n",
    ( unsigned int ) get_time(),
    thread_num
  );
}

void print_num_status_cnt( int thread_num, int cnt ) {
  printf(
    "t=%u\tThread %d\tCnt: %d\n",
    ( unsigned int ) get_time(),
    thread_num,
    cnt
  );
}

void print_status( char *thread_name ) {
  printf(
    "t=%u\tThread %s\n",
    ( unsigned int ) get_time(),
    thread_name
  );
}

void print_status_cnt( char *thread_name, int cnt ) {
  printf(
    "t=%u\tThread %s\tCnt: %d\n",
    ( unsigned int ) get_time(),
    thread_name,
    cnt
  );
}

void print_status_prio( char *thread_name ) {
  printf(
    "t=%u\tThread %s\tPrio: %u\n",
    ( unsigned int ) get_time(),
    thread_name,
    ( unsigned int ) get_priority()
  );
}

void print_status_prio_cnt( char *thread_name, int cnt ) {
  printf(
    "t=%u\tThread %s\tPrio: %d\tCnt: %d\n",
    ( unsigned int ) get_time(),
    thread_name,
    ( unsigned int ) get_priority(),
    cnt
  );
}

uint32_t print_fibs( int limit, int interval, uint32_t mod) {

  if ( interval == 0 ) interval = 1;

  int i = 1;
  uint32_t a = 0, b = 1, c;

  while (i < limit) {
    i++;
    c = (a + b) % mod;

    if ( i % interval == 0 ) {
      printf("Fib[ %d ] = %lu (mod %lu)\n", i, c, mod);
    }

    a = b;
    b = c;

  }

  return b;

}
