# 組み込み機器の特徴
本章では組み込みソフトウェアが制御対象とする
組み込み機器の特徴を概観する。

パーソナルコンピュータなどの汎用計算機に対して，
組み込み機器での演算処理には制約が存在する。
汎用計算機との比較から組み込み機器の制約を把握する。
制約によってソフトウェア開発が困難になる点を挙げ，
その回避方法を挙げる。

## 組み込み機器と汎用計算機の比較
以下に一般的な組み込み機器と汎用計算機の比較を示す。

| 特徴       | 組み込み機器 | 汎用計算機                     |
| ----       | ------------ | ----------                     |
| 演算速度   | 遅い         | 速い                           |
| メモリ容量 | 小さい       | 大きい                         |
| 入出力     | IOピンなど   | キーボード・マウス・画面       |
| OS         | 無いか簡易   | OSにより資源が抽象化されている |

## 演算資源の制約
組み込み機器は汎用計算機に比べコストを抑制するために，
演算装置の性能，メモリ容量といった演算資源が限られる場合が多い。
一方で組み込み機器はリアルタイム動作[^RealTimeOperation]が求められ，
指定された時間内に一定の処理を終了させたい場合が多い。
限られた資源の中で演算時間を短縮するため，
プログラムの読みやすさ，理解しやすさを度外視して，
速さを求めたプログラム記述となる場合もある[^SpeedOptimization]。
演算時間の短縮にはアルゴリズムの改良，データ構造の改良が効果的である。
しかし，これらの改良は開発が進んでからでは影響範囲が大きく困難となる。
開発処理の設計段階で検討しておくのがよい。

[^RealTimeOperation]: ここでいうリアルタイム動作とは，
何らかの入力があってから，処理が行われ，出力されるまでの時間遅れが
必ず一定の時間に収まることを意図している。

[^SpeedOptimization]: プログラムを書く上で優先すべきは人間にとっての
読みやすさ，理解しやすさである。
演算速度のためにわかりにくいプログラムを書き，
不具合を含んでは意味がない。
組み込みソフトウェア用のコンパイラの最適化性能が向上しており，
人間がわざわざ速度を求めた記述をしなくても良くなってきている。
細かい部分の最適化はコンパイラに任せ，
人間はアルゴリズムの改善やデータ構造の改善といった
コンパイラではできない部分に注力すべき。

## 入出力の制約
組み込み機器は入出力が限られるため，ソフトウェア動作を把握しにくい。
汎用計算機であれば，動作状態を逐一画面に表示して不具合箇所を特定できる。
組み込み機器ではソフトウェアの動作状態を確認できる情報は，
IOピンの電位変化，外部接続機器の動作状態など間接的なものとなる。
機器に組み込んでからの不具合調査は難易度が高い。
外部入出力などハードウェアが絡む部分は機器に組み込んでからしか動作を確認できないため仕方ないが，
ハードウェアに依存しない内部での演算処理は組み込む前に十分不具合を出しておくのが良い。

## OS有無による制約
組み込み機器では OS が無いか，簡易なものである。
OS が行うメモリ管理，割り込み管理，外部機器への入出力処理を
すべて自前で記述する必要がある。

