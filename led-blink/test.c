#include <stdio.h>
#include <assert.h>
#include "../include/virtual_microprocessor.h"

int main(int argc, char **argv) {
  int i;
  int status = 0;
  int count = 0;
  unsigned int previous_status = 0;
  for (i = 0; i < 100; i++) {
    interrupt();
    if (digitalout & (1<<0)) {
      if (status == 0) {
        status = 1;
        previous_status = 1;
      } else if (status == 1) {
        if (previous_status == 0) {
          previous_status = 1;
          status = 2;
          count = 0;
        }
      } else {
        if (previous_status == 0) {
          previous_status = 1;
          status = 2;
          assert(count == 10);
          count = 0;
        }
      }
    } else {
      if (status == 0) {
        status = 1;
        previous_status = 0;
      } else if (status == 1) {
        if (previous_status == 1) {
          previous_status = 0;
          status = 2;
          count = 0;
        }
      } else {
        if (previous_status == 1) {
          previous_status = 0;
          status = 2;
          assert(count == 10);
          count = 0;
        }
      }
    }
    count++;
  }
  printf("OK\n");
  return 0;
}
