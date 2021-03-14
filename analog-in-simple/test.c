#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  unsigned int error = 2;
  int i;
  for (i = 0; i < 100; i++) {
    float ref = (float)cos(2.0 * M_PI * (float)i / 30.0f) * 3.5f;
    analogin[0] = (unsigned int)((1.0f + ref / 5.0f) * 2048.0f);
    interrupt();
    if ((analogout[0] < (analogin[0] - error)) || (analogout[0] > (analogin[0] + error))) {
      printf("NG %d\n", i);
      return 1;
    }
  }
  printf("OK\n");
  return 0;
}
