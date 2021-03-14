#include <stdio.h>
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
  for (i = 0; i < 100; i++) {
    float v_dcm = dcm_v(v_in,0.0f);
    analogin[1] = get_dig(2.5f);
    analogin[0] = get_dig((v_in - v_dcm) / R);
    interrupt();
    v_in = get_v(analogout[0]);
    printf("%f %f %f\n", get_v(analogin[0]), get_v(analogin[1]), get_v(analogout[0]));
  }
  return 0;
}
