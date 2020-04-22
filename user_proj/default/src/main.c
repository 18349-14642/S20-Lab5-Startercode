#include <stdio.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, char const *argv[]){
  while(1){
    printf("Hello World from User : %s\n", argv[1]);
  }
  return 0;
}
