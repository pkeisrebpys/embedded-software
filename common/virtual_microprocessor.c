#include "../include/virtual_microprocessor.h"
unsigned int digitalin;// 32 bit デジタル入力。
unsigned int digitalout;// 32 bit デジタル出力。

unsigned short analogin[N_ANALOGIN];// 12 bit アナログ入力。
unsigned short analogout[N_ANALOGOUT];// 12 bit アナログ出力。


unsigned char serialin_buffer[SERIALIN_SIZE];// シリアル入力リングバッファ
unsigned int serialin_status;// 0 - 7 bit に読み込みデータの後端位置が入っている
unsigned char serialout_buffer[SERIALOUT_SIZE];// シリアル出力リングバッファ
unsigned int serialout_status;// 0 - 7 bit に書き込み完了したデータ後端位置が入っている。
unsigned int serialout_command;// 0 - 7 bit に書き込みデータのサイズを入力する。

