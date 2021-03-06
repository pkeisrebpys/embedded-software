# C言語の文法の基礎
## プログラムとプログラミング言語
プログラミング言語で記述されたプログラム (コード) はコンピュータが正しく認識できるだけでなく，
人間にもわかりやすいはずである。

プログラミング言語は様々な種類がある。
プログラムに近い記述のものを (ハードウェアに近いという意味で) 低水準言語，
抽象度を上げて**人間によりわかりやすく**した言語を高水準言語という[^HighLevelProgrammingLanguage]。
C言語は高水準言語に分類されるが，後述するポインタによってメモリを直接操作できるため，ハードウェアに対する細い操作が可能。

[^HighLevelProgrammingLanguage]: プログラミング言語を使うのは人間にわかりやすくするため。
人間同士でのやり取りが困難になるような読みにくいコードを買いてはプログラミング言語を使う意味が薄れる。

以降では，C言語を使ってプログラムを記述する上で必要な文法知識を，
大雑把に説明する。
正確な理解のためには規格の記述を参照すること。

## C言語の構成要素
C言語は細かいことを言わなければ，
データ保存場所を記述する変数と，
処理内容を記述する関数で構成されている。

変数の種類と関数の動作を理解できれば単純なプログラムが理解できる。

C言語の理解を難しくしているのはポインタと言われる。
しかし，メモリと変数の対応を理解できればポインタは難しくない。

以下では変数と実際のデータ保存場所であるメモリの対応を説明した後，
ポインタの概念，ポインタとメモリと変数の関係を説明する。
そして変数に格納されたデータを使って実際の処理を行う関数の動作について説明する。

### 変数とメモリの対応
変数は演算処理に必要なデータの保存場所を示す。
変数の種類によって保存場所の大きさと，データの認識のされ方が変化する。

主な変数の種類は以下。

```c
/* 符号付き整数値を保存する場所を示す。
   最近の汎用計算機では 32 bit (4 byte) のデータ保存場所を示し，
   -(2^31) から (2^31 -1) までの整数を扱える。
   int 型に対してデータサイズの明確な決まりはないため，
   扱う機器によっては int が 16 bit であったりする場合もある。 */
int a; 

/* 符号無しの整数値を保存する場所を示す。
   データとして見れば int 型と変わらないが，値として読むときに
   最上位bitを符号ではなく値の一部として認識する。
   32 bit の場合は 0 から (2^32 -1) までの整数を扱える。 */
unsigned int b;

/* int 型， unsigned int 型よりデータサイズが小さい整数値の保存場所。
   最近の汎用計算機では 16 bit (2 byte) のデータ保存場所を示す。 */
short c;
unsigned short d;

/* 文字データを保存する場所を示す。
   日本語の文字は 2 byte 以上を使うが，
   英数字は 1 byte であるため，この変数は 1 byte (8 bit) の整数を保存する場所を示す。 */
char e;
unsigned char f;

/* int 型， unsigned int 型と同じかより大きい
   データサイズの整数値を保存する場所を示す。
   最近の汎用計算機では int 型と同じ 32 bit (4 byte) の場合が多い。
   扱う機器によって 32 bit ではない場合がある。 */
long g;
unsigned long h;
long int i;
unsigned long int j;

/* long 型， unsigned long 型より大きいデータサイズの整数値の保存場所を示す。
   最近の汎用計算機では 64 bit (8 byte) であることが多い。 */
long long k;
unsigned long long l;
long long int m;
unsigned long long int n;

/* 4 byte (単線度)浮動小数点数を保存する場所を示す。
   不動小数点数については科学計算で用いる有効桁数の記述をイメージすると良い。
   浮動小数点数では指定された有効桁数の値とその指数に分けてデータを保存する。
   指数表記のため大きなレンジの値を表現できる。
   4 byte のデータを使用するが，そのうち有効桁として使える範囲が限られるため，
   演算を繰り返した場合の値の精度は 4 byte の int 型に劣る。
   */
float x;
   
/* 8 byte (倍線度)浮動小数点数を保存する場所を示す。
   float 型より有効桁数が大きく，4 byte の int 型よりも精度が高い。
   演算負荷が大きい難点がある。*/
double y;
```

以上が主な変数の種類である。
データ型のサイズ (byte) は `sizeof(int)` のように取得できる。
最低限これらの変数を並べれば，演算処理に必要なデータ保存場所を記述できる。
しかし，順番が重要な連続したデータを保存したい場合や，
グループにまとめて扱いたいデータの場合，
変数を並べるだけでは不便である。

連続したデータを保存するためには配列が用意されている。

```c
/* 以下は int 型のデータ保存場所が連続して 13 個用意されることを示す。
   これまでの変数の記述に [用意したい数] を付け加える。 */
int data[13];
```

配列で指定したデータ保存場所はメモリ上で連続している。
このことは後から出てくるポインタでのメモリ位置指定と深く関わる。
配列の要素へのアクセスは次のように `[]` を用いる。
1 番目のデータからの移動量を示すため， `[0]` から始まる。

```c
int n = data[0];
```

グループにまとめたいデータは構造体を用いる。

```c
/* 以下は 1 個の int 型データと 3 個の float 型データを group_name という構造体でまとめている。
group_name 構造体のデータ保存場所の一つを a_group として確保している。 */
struct group_name
{
  int n;
  float x;
  float y;
  float z;
} a_group;
```

構造体も配列と同様，メモリ上の連続した場所にデータが保存される。
論理的にも，データ配置上も関連性がありまとまっていることを示す。
構造体の構成要素は次のように `.` をもちいてアクセスする。

```c
a_group.n = 2;
```

基本的にはこれらの変数をうまく組み合わせて演算に必要なデータを保存する。

### ポインタとメモリと変数の関係
プログラム内で変数として確保したデータ保存場所へは，
変数名を使って読み込み，書き込みができる。
しかし，外部入出力などプログラム外で決められたデータ保存場所は，
変数で確保した場所とことなり，これまでの変数では参照できない。

そこで，メモリアドレス上の任意の場所をアドレスを直接指定して参照するのが，
ポインタである。
以下のプログラムの一部では，メモリアドレス 0x99990000 が AD 変換器に割り当てられており，
0x99990000 を読み出すことで符号なし整数値として AD 変換値を取得できると想定している。
プログラムではまず，メモリアドレス 0x99990000 にある符号なし整数を指すポインタとして ADC_value を定義している。
ポインタは `*` の記号を用いて表す。

ADC_value が指し示している AD 変換値を取得するにはポインタ名に `*` をつける。
これで指し示しているメモリアドレスに保存されている値を取得して変数 x にコピーできる。

ポインタ名に `*` をつけなかった場合，
ポインタが指しているメモリアドレスに保存されている値ではなく，
アドレス値自体を取得する。
変数 addr にはアドレスである 0x99990000 が保存される。

```c
unsigned int *ADC_value = 0x99990000;
unsigned int x;
unsigned int addr;
x = *ADC_value;
addr = ADC_value;
```

ポインタはこのようにプログラムで直接管理していない場所のアドレスを直接指定して読み書きするために使うことができる。
また，プログラムが管理している配列などもポインタで読み書きすることができる。

以下では，配列 data の先頭のアドレスを addr にコピーし，
addr を起点に配列 data の内容を読み出している。
変数 data 自体からは保存されたデータではなくメモリアドレスが取得できる。
取得したポインタ addr の指す場所は data の 1 個目の値があるため，
x には data の 1 こめの値がコピーされる。

ポインタは指定されたデータ型のサイズ分だけ参照位置を前後にずらすことができる。
ポインタに対して + 0 するともとの場所を示すので，
やはり x には data の 1 こめの値がコピーされる。

ポインタに対して + 1 すると，もとの場所より int 型で1個後ろのデータを指すので，
y には data の 2 こめの値がコピーされる。
同様に + 2 すると参照先が int 型で 2 個後ろになるため
z には data の 3 こめの値がコピーされる。

```c
int data[13];
int *addr = data;
int x = *addr;
int x = *(addr + 0);
int y = *(addr + 1);
int z = *(addr + 2);
```

ここで注意が必要なのは，
ポインタはあくまで指定されたデータ型のサイズずる参照先を移動させることである。
もし addr が short 型であれば short 型のサイズだけ移動するため，
同じ数を足しても int 型の場合よりもおそらく移動量は小さくなる。

よくある勘違いとしてポインタはアドレスを表しているから，
1足せばアドレスが1増える，つまり 1 byte 移動すると間違えることがある。
int 型が 4 byte であれば int 型のポインタに1を足すと，参照先は 4 byte進むことになる。

このような勘違いを防ぐとともにポインタによる参照の記述を簡易にする方法として，
以下の記述がある。
以下の記述は上の例と同じ結果が得られる。
ポインタに 1 を足すことは addr[1] のように記述できる。

```c
int data[13];
int *addr = data;
int x = *addr;
int x = addr[0];
int y = addr[1];
int z = addr[2];
```

そもそも，配列は以下のように各データを参照できる。
ポインタでの簡易な参照方法と同じ記述である。
(本当は配列と同じ記述をポインタにも流用した)

```c
int data[13];
int x = data[0];
int y = data[1];
int z = data[2];
```

構造体へのポインタを用いた参照は次のとおり `->` を用いて行う。
`&` は変数のアドレスを取得する。

```c
struct group_name {
  int n;
  float x;
  float y;
  float z;
} a_group;

struct group_name *addr = &a_group;
addr->x = 1.0;
addr->y = 2.0;
addr->z = 3.0;
```

以下のようにもアクセスできるが，演算の優先度を示すために `()` が必要となる。
```c
(*addr).x = 1.0;
```

### 配列やポインタの危険性
配列やポインタはメモリのアドレスを指定してその場所の値を取得できる。
これはプログラムが管理するメモリだろうが，それ以外だろうが可能である。
非常に自由度が高いが，いくらでもプログラムの動作を破壊する危険なことが可能でもある。

以下のプログラムは配列で確保したデータサイズを超えて，メモリを読んでいる。
配列 data のサイズは 4 であり，データは data[0], data[1], data[2], data[3] の 4 箇所に保存されている。
data[4] は一見 data の 4 番目のようで正しそうだが，
`[]` で表すのは 1 番目のデータからの移動量であるから，
これは存在しない 5 番目のデータを読もうとしている。
存在しない 5 番目のデータを読んだ場合の動作は場合による。
以下の場合はプログラム上は data の次に a が存在している。
メモリ上でもプログラムの通りに変数が並べられていれば，
data[4] により a の値が読まれる。
ただし，メモリ上にどのように変数を配置するか，そもそもメモリ上に変数を配置するか，レジスタ上だけに一時的に置くかはコンパイラが決定するため，
必ずしも a が読まれるとは限らず，
全く予期しない結果となる場合もある。

```c
int data[4];
int a;
int b;
int c;
int x = data[4];
```

### 関数とその動作
ここまでで，演算に必要なデータの保存場所の確保，外部データへの読み書きができるようになった。

次に実際の処理を記述する関数を説明する。
以下に非常に簡単な関数を示した。
この関数 ADC_get は int 型のデータ ch を受け取り， unsigned int 型のデータを出力する。
関数の入力にあたる `()` 内の値を引数，
出力されるデータを返り値という。
外部からみた関数は引数を入力とし，返り値を出力することだけが決められている。

```c
unsigned int ADC_get(int ch)
{
  return ADC_base_address[ch];
}
```

C言語のプログラムは main という関数が呼び出されたあと，
main に決められた処理に加えて様々な関数を呼び出していくことで構成されている。
個々の関数の処理は単純であっても，
関数を組み合わせることで全体として目的の機能を実現する。

なお，返り値として出力できる値は return で示す 1 つのみである。
複数のデータを返したい場合は引数としてポインタもしくは配列を受け取り，
ポインタが指す場所を関数内で直接書き換えることで実現する。

よくある勘違いとしてポインタや配列ではない値を引数として受け取り，
その値を書き換えることで，関数外への出力とすることである。
関数の引数は関数に入力されるときに元の変数とは別個にコピーされる。
このため関数内で使う引数と関数外から与えた変数は別個のものとなる。
いくら関数で引数を変えても関数外の値を変えることはできない。
以下がよくある誤りである。
2引数のデータを入れ替えようとしているが，これは意味をなさない。

```c
void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

void main(void)
{
  int a = 1;
  int b = 2;
  swap(a, b);
}
```

以下のようにポインタとしてアドレスを受け渡すべき。
なお swap の呼び出しで変数に `&` をつけることで，
その変数のアドレスを取得することができる。

```c
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void main(void)
{
  int a = 1;
  int b = 2;
  swap(&a, &b);
}
```

個々の関数内では実行したい処理を順に並べてあるだけである。
ただし，次に取り上げる条件分岐によって状況に応じた処理を実行できるようにする。

### 条件分岐
条件分岐の基本は if 文である。
以下の関数 func は 1 つの条件分岐を含む。
引数で入力された c が 23 の場合， 47 を出力する。
それ以外の場合 97 を出力する。

```c
int func(int c)
{
  if (c == 23) {
    return 47;
  } else {
    return 97;
  }
}
```

else 以降は省略することも可能である。
この条件分岐は次のようにもかける。

```c
(c == 23) ? 47 : 97;
```

複数の条件分岐も可能。

```c
int func(int c)
{
  if (c == 23) {
    return 47;
  } else if (c == 67) {
    return 37;
  } else {
    return 97;
  }
}
```

条件分岐と goto 文を用いれば繰り返し処理も実現できる。
以下の処理は i を繰り返し回数のカウンタとして用い，
x に 0 から 9 まで 10 回の加算を行う。

```c
int x = 0;
int i = 0;

loop:
if (i < 10) {
  x += i;
  i++;
  goto loop;
}
```

このような処理をよりわかりやすく記述するために for 文が存在する。
for 文では開始前の処理，繰り返し条件，それぞれの繰り返し終了時の処理を
`;` でくぎって記述する。

```c
int x = 0;
int i;
for (i = 0; i < 10; i++) {
  x += i;
}
```

繰り返し回数を指定せず，条件を満たすまで処理を行う場合は以下のように記述する。
以下の処理では x は 2 の累乗で増加していく。
x が 100 以上となった場合繰り返しを終了する。
この場合は 6 回実行され x = 128 となったときに処理が終了する。

```c
int x = 2;
while (x < 100) {
  x = x * x;
}
```

繰り返し処理の途中で終了する場合は `break` を，
繰り返し処理の途中でその繰り返しを終了し，次の繰り返しに入る場合は `continue` を用いる。

繰り返し処理は goto 文を用いても， for 文を用いても， while 文を用いても実現できる。
ただし，読みやすさを考えると，
繰り返し回数が指定されている場合はカウンタを条件とした for 文，
繰り返し回数は不定だが，条件到達まで実行する場合は while 文といったように，
処理内容に応じて使い分けるとよい。

goto 文は世間一般では嫌われることが多いが，
エラー終了時の処理を記述する場合に用いられることがある。
以下では other_process1, other_process2 が正常の場合 0 を返し，
異常の場合 0 以外を返すとしている。
0 以外で異常が見られる場合はその場で error_process を実行し，
some_process 自体もエラーを示すため 0 以外の値である -1 を返す。
すべての処理が成功したら成功を示すため 0 を返す。
(成功時に 0 を返す関数はC言語の標準ライブラリに多く見られる。)

```c
int some_process(void)
{
  if (other_process1() != 0) {
    goto error;
  }
  if (other_process2() != 0) {
    goto error;
  }
  return 0;
  error:
  error_process();
  return -1;
}
```

## 宣言と定義
ここまで，変数と関数の説明をしてきた。
説明の中で記述していた変数や関数は宣言であり，定義であった。
ここでは，宣言と定義の違いを説明する。

宣言 declaration はその名の通り，このような変数，関数を使いますよという宣言である。
実際にそのような変数，関数が存在するかは関係なく，
宣言したような型を持つ変数，関数があったとしてプログラムを記述する。
宣言されていない変数，関数を使用することは許されないため，
変数，関数の使用前には必ず宣言が必要である。

定義 edefinition は実際に変数，関数の実体をつくるための記述である。
定義として記述した変数はメモリなどにデータ保存場所を確保される。
定義として記述した関数は命令のまとまりとしてプログラムデータに加わる。
定義は変数，関数に実体を持たせるため，
1プログラムの中である変数，関数の定義は一箇所のみでなければならない。

これまでの例で出てきた変数，関数はこのようなものを使いますという宣言をしながら，
プログラム中の実体データとして加わる定義でもあった。
宣言と定義が同時に行え，記述が単純で楽だが，
宣言と定義を分けて記述した方が良い場合がある。

以下に例としてプログラムを複数のファイルに分割する場合を考える。
あるファイル A.c にグローバル変数として int data; の定義が存在したとする。
別のファイル B.c では A.c で定義された int data; を使用するとする。
コンパイラは 1 つの c ファイルごとにコンパイルを実行するため，
B.c をコンパイルする際には int data; の宣言も定義もない状態となる。

ここで B.c にもグローバル変数として int data; の定義を追加する。
これによって B.c のコンパイルは成功する。
しかし， A.c と B.c を組み合わせて 1 つのプログラムにしようとする (これをリンクするという) と，
int data; について 1 プログラムに 1 定義の決まりが守られていないため，リンクに失敗する。

B.c に int data; の定義ではなく，宣言を追加する。
この場合は A.c という別ファイルに定義は存在しますよという意味をこめて以下のように記述する。

```c
extern int data;
```

この extern をつけることで，他のファイルに定義された変数もしくは関数を使用するという宣言となる。
なお，関数の宣言については extern をつける必要はなく，以下のように記述する。

```c
unsigned int ADC_get(int);
```

宣言を行うことで，他のファイルに定義された変数，関数を使用することができる。

(補足: C言語では 関数，制御ブロック内の変数定義は関数，制御ブロック先頭でしかできない。
途中に処理をはさんでから定義するとコンパイラに怒られる。
なお他の言語では処理途中，変数使用の直前に定義することが許されている場合が多い。)

## 変数と関数の有効範囲
ここまでで，とりあえず処理に必要なメモリの確保，処理の記述ができる。
しかしながら，変数や関数の有効範囲を把握しないと思わぬ罠にはまる場合がある。

変数は記述された場所によってその有効範囲が異なる。
ここで言う有効範囲は以下の2つの意味がある。

- メモリ上に変数が存在している期間 (生存期間)
- 変数を参照できるプログラム上の場所 (スコープ)

### 生存期間
生存期間は変数が定義される場所，方法によってことなる。
変数を定義する場所と生存期間は以下の通り。

- 関数の外で static をつけない (グローバル変数)
  - プログラム開始から終了までメモリ上に存在
- 関数の外で static をつける (static 変数)
  - プログラム開始から終了までメモリ上に存在
- 関数の中で static をつけない (ローカル変数)
  - 関数呼び出し時にメモリ確保され，終了時に消滅，場合によってはレジスタ上のみ
- 関数の中で static をつける (static 変数)
  - プログラム開始から終了までメモリ上に存在
- 制御ブロックの中で static をつけない (ローカル変数)
  - 制御ブロックに入った時点でメモリ確保され，制御ブロックを出たときに消滅，場合によってはレジスタ上のみ
- 制御ブロックの中で static をつける (static 変数)
  - プログラム開始から終了までメモリ上に存在

ここで制御ブロックとは if 文や for 文などのように `{}` で囲まれた範囲である。
if 文や for 文でなくても `{}` だけをつけても制御ブロックとなる。

プログラム実行中常に存在するのはグローバル変数と static をつけて定義された変数である。
その他のローカル変数はそれぞれの制御ブロックの間のみ存在する。

なお関数についてはプログラムデータとして常に存在する。

### スコープ
変数を参照できる範囲であるスコープも変数の定義，宣言場所，方法によって異なる。

- 関数の外で static をつけない (グローバル変数)
  - プログラム上のどこからでも参照できる。ファイル外の場合は使用前に extern 宣言が必要。
- 関数の外で static をつける (static 変数)
  - 定義されたファイル内からのみ参照可能。他ファイルからは参照不可。
- 関数の中の変数 (ローカル変数) 引数を含む
  - 関数の中でのみ参照できる。他の関数や呼び出し先では参照不可。
- 制御ブロックの中の変数 (ローカル変数)
  - 制御ブロックの中でのみ参照できる。制御ブロック外や制御ブロック中で呼び出した関数内では不可。

グローバル変数を参照するための extern 宣言のスコープも関数，制御ブロックにより制限できる。

関数のスコープについては基本はグローバル変数と同じである。
static をつけるとそのスコープはファイル内となる。

### 有効範囲の適切な選択
生存期間，スコープともに必要十分な範囲を選択するべきである。

長過ぎる生存期間を変数に与えるとメモリ容量を無駄に消費することになる。
また，コンパイラ最適化が正しく行われず，遅いプログラムになる可能性がある。

大きすぎるスコープはプログラムを読み書きする上で考慮すべき点が増加する。

## volatile と const
組み込みソフトウェアでは volatile がよく現れる。
volatile プログラムが把握していない場所でその変数の値が変化しうることを示す。
これにより，通常のプログラムでは変化しないと考えられ，場合によってはコンパイラにより削除される処理を，
記述の通りに実行させることができる。
使用例としては以下。

- 外部入出力部であり，プログラム外で書き換えられた値を読み書きする場合
- 関数処理中に割り込みが発生し，他の関数により値が書き換えられる場合

```c
volatile unsigned int *ADC_buffer = 0x99990000;
unsigned int ADC_get(int ch)
{
  return *(ADC_buffer + ch);
}
```

```c
volatile int isFinished = 0;
int wait_other_process(void)
{
  while (isFinished == 0) {
  }
  return 1;
  
}
```

## コメント
`/* このコメントは /* */ に挟まれた間，改行を含めてコメントとなる */` もしくは
`// この形式のコメントは行末まで。次の行は通常のプログラム.`  の形で入れる。

コメントはあくまでプログラムで表現できない点を記述するものと考えた方がよい。
プログラムで表現されたことをコメントに書いた場合，
プログラムとコメントの一貫性の管理という余計な作業が増える。

例えばプログラムは変更したが，その動作内容を示したコメントを変更しなかった場合，
プログラムが示す動作とコメントが示す動作が食い違う。
プログラム実装に誤りがあるのか，ただのコメント修正漏れか混乱をきたす。

プログラムの動作を書きたくなるのは，プログラムの記述が良くない可能性がある。
プログラム言語は機器の動作を人間にもわかりやすく記述するものであるから，
動作内容はプログラムを読めば理解できるはずである。
速やかに理解できないプログラムは，動作に対する十分な理解がないか，推敲されていないプログラムである。
そこには不具合が含まれる可能性を疑った方が良い。

プログラムに入れるコメントとして適切なものは，プログラム実装の背景や使用上の注意点などが挙げられる。
例えばプログラムの利用目的，入出力値が取るべき条件など。

## 個々の演算
関数内の処理については細かく見てこなかった。
ここでは代表的な演算を説明する。

```c
int x = 1; // 値を代入するときは = を用いる。必ず 左の変数に代入する。
int y = x; // x の値を yに代入する。x の値は影響を受けず， y の値が変化する。
x = +x; // 符号反転なし。
x = -x; // 符号反転する。
int z = x + y; // 加算。オーバーフローに注意する。
int z = x - y; // 減算。アンダーフローに注意する。
int z = x * y; // 乗算。演算負荷が大きい。オーバーフローに注意する。
int z = x / y; // 除算。演算負荷が更に大きい。y == 0 の場合に注意する。
int z = x % y; // x / y の剰余を得る。演算負荷が大きい。
int z += x; // z = z + x; と同じ
int z -= x; // z = z - x; と同じ
int z *= x; // z = z * x; と同じ
int z /= x; // z = z / x; と同じ
int z %= x; // z = z % x; と同じ
```

ビット演算
```c
unsigned int r = 0xffffffff;
unsigned int s = 0x0000ffff;
unsigned int t = r & s; // r と s の bit AND
t = r | s; // r と s の bit OR
t = r ^ s; // r と s の bit XOR
t = ~r; // r の bit NOT
t = r << 1; // r を左に 1 bit シフト 正数の場合 r * 2 に相当
t = r >> 1; // r を右に 1 bit シフト 正数の場合 r / 2 に相当
t &= r; // t = t & r と同じ
t |= r; // t = t | r と同じ
t ^= r; // t = t ^ r と同じ
t <<= 1; // t = t << 1 と同じ
t >>= 1; // t = t >> 1 と同じ
```

以下は間違いやすいので，繰り返しカウンタの更新などで，
単独で使うことを推奨する。
```c
z = x++; // x を z に代入してから x += 1 する。
z = x--; // x を z に代入してから x -= 1 する。
z = ++x; // x += 1 してから，z に代入する。
z = --x; // x -= 1 してから，z に代入する。
```

ポインタ，アドレス関連
```c
unsigned int data;
unsigned int *addr = &data; // data のアドレスを取得する。
unsigned int x = *addr; // addr の指す場所のデータを取得する。
*addr = x; // addr の指す場所に x を代入する。
```

論理演算は真のとき 1，偽のとき 0 を返す。
0は偽として扱われ，0以外は真となる。
```c
unsigned int x = 0;
unsigned int y = 2;
unsigned int z = 2;
int ret;
ret = (x == y); // x と y が等しいとき真。ret == 0 となる
ret = (z == y); // x と y が等しいとき真。ret == 1 となる
ret = (x != y); // x と y が異なるとき真。ret == 1 となる
ret = (z == y); // x と y が異なるとき真。ret == 0 となる
ret = (x < y); // x が y より小さいとき真。 ret == 1 となる
ret = (x > y); // y が x より小さいとき真。 ret == 0 となる
ret = (z >= y); // y が z 以下とき真。 ret == 1 となる
ret = (z <= y); // z が y 以下とき真。 ret == 1 となる

ret = (x && y); // x と y の論理 AND，x == 0 で偽のため ret == 0
ret = (z && y); // z と y の論理 AND，ret == 1
ret = (x || y); // x と y の論理 OR，ret == 1
ret = !x;// x の論理 NOT ret == 1。
```

## 型変換
あるデータ型から異なるデータ型への変換を行うには以下のように変換する型を `()` で記述する。

```c
float y = 1.0f; // float 型であることを示すため f をつける。つけないと double 型となる。
double x = (double)y;
```

型変換は `()` で指定していない場合も異なる型同士の演算が行われる場合に自動的に行われる。
基本的にはより大きなデータサイズの型に変換される。
型は int 型， double 型になりやすい。

以下の乗算は double 型で行われたあと，float型に変換される。
意図しない型変換で演算速度が低下する。
```c
float x = 1.0f;
float y = x * 2.0; // 2.0 は double 型
```

以下のビット演算は int 型で行われたあと， short 型に変換される。
```c
short x = 0xff00;
short y = x | 0x0ff0;
```

## ファイル分割と include
コードが長大になる場合，プログラムを機能ごとのまとまりで分割したくなる。
複数の c ファイルに分割した場合，前述したようにファイルごとにコンパイルが行われたあとに，
リンクすることで 1 つのプログラムとなる。

ファイル分割したときに，個々のファイルの関数やグローバル変数を他のファイルで使いたい場合がある。
このようなときは他のファイルでは宣言を記述する必要がある。
宣言の記述は元にするファイルの内容と対応するから 1 パターンであるが，
宣言は元ファイルの関数，変数を利用するすべてのファイルで行う必要がある。

宣言を複数回記述することを避けるために，宣言をヘッダファイルにまとめ，includeする方法がある。

通常，元ファイル名と同じファイル名.h のような名前をつけたヘッダファイルに元ファイルの関数，変数の宣言を連ねる。
このファイルを使用先ファイルで以下のように include する。
以下では元ファイルを `sample.c` とする。

```c
#include "sample.h"
```

この記述はコンパイル前に sample.h の内容に置き換えられ，
コンパイル時には sample.h の内容が記載されているかのように動作する。

ヘッダファイルには関数，変数の宣言の他に，データ型の定義や定数の定義も加えたくなる。
データ型の定義は以下のようなものである。

```c
typedef struct group_name {
  int n;
  float x;
  float y;
  float z;
} group_name_t;
```

これは struct groupname 型に対して新たに group_name_t という型名をつけている。
以降では以下のように構造体を定義できる。

```c
group_name_t a_group;
```

この typedef は型定義であるから， 1 ファイルにつき 1 回のみ存在すべきである。
ヘッダファイルは場合によっては入れ子になり，複数回読み込まれる場合がある。
これを避けるために減っだファイルの先頭と末尾には以下のような記述を行う。

先頭
```c
#ifndef SAMPLE_H
#define SAMPLE_H
```

末尾
```c
#endif
```

これにより，一度 include されたヘッダファイルが 2 回目 include されると，
既に SAMPLE_H が定義されているため，ifndef の条件が成り立たず，内容が無視される。

型定義と同様に定数のマクロ定義も複数回行えないため，上の記述の中に収める。

```c
#define SOME_CONSTANT (1000)
```

