# 入出力の定義と内部ロジックの隠蔽
より理解しやすく，修正しやすいソフトウェアとするためには，
各機能，装置の入出力内容，制約を明確に定義しておくことが役に立つ。
機能，装置を外から見たときの入出力や制約が決まっていれば，
それを利用する側からは機能，装置内部でどのような動作が行われていてもかまわない[^BlackboxExample]。
必要十分な入出力定義がなされており，その通りに動作する限り，
機能内部がどのように作られているのかを知る必要がなくなる。

[^BlackboxExample]: 例えばエアコンが冷風・温風の両方を出せることを説明するにはヒートポンプの動作を知る必要がある。
しかし一般の消費者がエアコンを利用する上では，
そのようなエアコン内部の動作を知る必要はない。
消費者が知っておく必要があるのは，
リモコンの操作とエアコンの動作の対応関係くらいである。
リモコンへの入力に対し，エアコンが温風を出すか冷風を出すかが重要であり，
内部の動作を知ることは必要ではない。

実際のソフトウェアであれば，
関数宣言とともに引数や返り値の条件，実行時の条件が与えられていれば，
その関数を利用する上で，いちいち関数の定義を読む必要はなくなる。
関数内部の詳細までたどる必要がなくなるため，
ソフトウェアを読む側は全体の理解に力を振り分けることができる。

入出力が明確に定義された関数を修正する場合にも