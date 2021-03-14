#include <math.h>
#include <stdio.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  int i;
  for (i = 0; i < 100; i++) {
    float ref = (float)cos(2.0 * M_PI * (float)i / 30.0f) * 3.5f;
    analogin[0] = (unsigned int)((1.0f + ref / 5.0f) * 2048.0f);
    interrupt();
    printf("%f\n", (float)(analogout[0] - 2048)/2048.0f*5.0f);
  }
  return 0;
}
