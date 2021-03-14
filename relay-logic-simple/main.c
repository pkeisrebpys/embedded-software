#include <stdio.h>
#include "../include/virtual_microprocessor.h"

void print_relay(void) {
  int i;
  for (i = 0; i < 8; i++) {
    if (digitalin & (1<<i)) {
      printf("*");
    } else {
      printf("-");
    }
  }
}
void print_led(void) {
  int i;
  for (i = 0; i < 4; i++) {
    if (digitalin & (1<<i)) {
      printf("-");
    } else {
      printf("*");
    }
  }
}

void testcase(unsigned int in) {
  digitalin = in;
  interrupt();
  print_relay();
  printf(" ");
  print_led();
  printf("\n");
}
int main(int argc, char **argv) {
  unsigned int i;
  for (i = 0; i < 0x100; i++) {
    testcase(i);
  }
  return 0;
}
