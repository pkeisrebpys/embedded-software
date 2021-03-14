#include <stdio.h>
#include <stdlib.h>
#include "../include/virtual_microprocessor.h"

const float R = 1.0f;
const float M = 10.0f;

float dcm_v(float v, float load_torque) {
  static float inner_v = 0.0f;
  float i = (v - inner_v) / R;
  inner_v += (i - load_torque) / M;
  return inner_v;
}

float get_v(unsigned int dig) {
  if (dig >= 4096) {
    dig = 4095;
  }
  return 5.0f / 2048.0f * ((int)dig - 2048);
}
unsigned int get_dig(float v) {
  if (v >= 5.0f) {
    return 4095;
  }
  if (v < -5.0f) {
    return 0;
  }
  return 2048.0f * (1.0f + v / 5.0f);
}
int main(int argc, char **argv) {
  int i;
  float v_in = 0.0f;
  int count = 0;
  int error = 2;

  for (i = 0; i < 100; i++) {
    float v_dcm;
    if ((i / 20) % 2 == 0) {
      v_dcm = dcm_v(v_in,0.5f);
      analogin[1] = get_dig(0.5f);
    } else {
      v_dcm = dcm_v(v_in,-0.5f);
      analogin[1] = get_dig(-0.5f);
    }
    analogin[0] = get_dig((v_in - v_dcm) / R);
    if (abs(analogin[0] - analogin[1]) > error) {
      count++;
      if (count > 3) {
        printf("NG\n");
        return 1;
      }
    } else {
      count = 0;
    }
    interrupt();
    v_in = get_v(analogout[0]);
  }
  printf("OK\n");
  return 0;
}
