#include <stdio.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  int i;
  for (i = 0; i < 100; i++) {
    interrupt();
    printf("%f\n", (float)(analogout[0] - 2048)/2048.0f*5.0f);
  }
  return 0;
}
