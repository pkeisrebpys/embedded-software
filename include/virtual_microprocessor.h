#ifndef VIRTUAL_MICROPROCESSOR_H
#define VIRTUAL_MICROPROCESSOR_H
/*
 * デジタル外部入出力
 * 0-31bitがそれぞれ外部機器と接続されている。
 */
extern unsigned int digitalin;// 32 bit デジタル入力。
extern unsigned int digitalout;// 32 bit デジタル出力。

/*
 * アナログ外部入出力
 * 外部電圧 -5 から +5V と 0 から 4095 の値を相互変換する。
 * チャンネル数は入出力それぞれ 8 チャンネル。
 */
#define N_ANALOGIN (8)
#define N_ANALOGOUT (8)
extern unsigned short analogin[N_ANALOGIN];// 12 bit アナログ入力。
extern unsigned short analogout[N_ANALOGOUT];// 12 bit アナログ出力。


/* 
 * シリアル入出力
 * 入出力それぞれに 256 byte のリングバッファを備える。
 * 受信確認は省略したため，受信していなくてもデータが到着したら上書きされる。
 * 送信確認は省略したため，送信していなくてもデータを書き込むと上書きされる。
 * 今回は模擬のため，最大の256バイト書き込んでも割り込み周期の間に送信完了するとした。
 */
#define SERIALIN_SIZE (256)
#define SERIALOUT_SIZE (256)
extern unsigned char serialin_buffer[SERIALIN_SIZE];// シリアル入力リングバッファ
extern unsigned int serialin_status;// 0 - 7 bit に読み込みデータの後端位置が入っている
extern unsigned char serialout_buffer[SERIALOUT_SIZE];// シリアル出力リングバッファ
extern unsigned int serialout_status;// 0 - 7 bit に書き込み完了したデータ後端位置が入っている。
extern unsigned int serialout_command;// 0 - 7 bit に書き込みデータのサイズを入力する。

/*
 * 1ms 割り込み関数。
 * 本関数に記述した処理が 1ms ごとに実行される。
 */
void interrupt(void);

#endif
