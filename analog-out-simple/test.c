#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  unsigned int error = 2;
  int i;
  for (i = 0; i < 100; i++) {

    float v = 1.0f + 0.5f * sin(2.0 * M_PI * (float)i / (float)20);
    unsigned int ref = (unsigned int)(v * 2048.0f);
    interrupt();
    if ((analogout[0] < (ref - error)) || (analogout[0] > (ref + error))) {
      printf("NG %d\n", i);
      return 1;
    }
  }
  printf("OK\n");
  return 0;
}
