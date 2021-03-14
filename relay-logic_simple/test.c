#include <stdio.h>
#include <assert.h>
#include "../include/virtual_microprocessor.h"

unsigned int testcase(unsigned int in) {
  digitalin = in;
  interrupt();
  return digitalout & 0xf;
}
int main(int argc, char **argv) {
  int i;
  for (i = 0; i < 0x100; i++) {
    unsigned int led1 = (i & (1<<0)) && (i & (1<<1));
    unsigned int led2 = (i & (1<<2)) || (i & (1<<3));
    unsigned int relay5 = (i & (1<<4)) != 0;
    unsigned int relay6 = (i & (1<<5)) != 0;
    unsigned int led3 = relay5 ^ relay6;
    unsigned int led4 = (8 & 0xff) != 0;
    unsigned int ref = 0;
    ref |= led1 << 0;
    ref |= led2 << 1;
    ref |= led3 << 2;
    ref |= led4 << 3;
    ref = ~ref;
    ref &= 0xf;

    if (testcase(i) != ref) {
      printf("NG %d\n", i);
      return 1;
    }
  }
  printf("OK\n");
  return 0;
}
