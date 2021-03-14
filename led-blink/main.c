#include <stdio.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  int i;
  for (i = 0; i < 100; i++) {
    interrupt();
    if (digitalout & (1<<0)) {
      printf("-");
    } else {
      printf("*");
    }
  }
  printf("\n");
  return 0;
}
