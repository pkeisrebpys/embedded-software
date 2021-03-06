# ソフトウェア変更点の管理
バージョン管理システムを用いてファイル変更差分を記録する。

誰が，いつ，どのような変更を行ったのかが自動で記録できる。
変更に対して適切なコメントを残せば，
その変更が何を目的として行われたのか，変更の背景も記録することができる。

バージョン管理システムを用いて変更差分を記録しておけば，
任意の時点のソフトウェアを取得することができる。
直近の変更で不具合が生じた場合に，
原因となった変更点が明確になるとともに，
最悪の場合，不具合が生じていないバージョンのソフトウェアに巻き戻すことができる。

複数名でソフトウェアの変更を行った場合，
バージョン管理システムを用いない場合は人手で差分を調査し，
適用する変更と適用すべきでない変更を分別する必要がある。
分別を誤れば，修正されたはずの不具合が再現する。

バージョン管理システムを用いる場合，
他者による変更が既に行われていても，多くの場合自動で変更点を反映できる。
変更箇所の重複があり，自動で反映できない場合も，
他者が行った変更の内容と目的が参照できる。
変更されたコードのみから差分を確認するのに比べ，作業は容易になる。

ソフトウェア開発の状況によっては，
複数のバージョンのソフトウェアが時間的に平行して開発される場合がある。
平行しているバージョンには共通部分の不具合修正などに，共通して適用すべき部分と，
それぞれのバージョンに特有の部分が混在する。
このような場合，人手に頼る場合は2つのバージョン A B のプログラムの差分をとり，
A から B に写すべき変更，
B から A に写すべき変更，
A だけの変更，B だけの変更，
を区別しなければならない。
本当は A 側が正しく A から B に写すべき変更を，
誤って B から A に写してしまう間違いが生じる。
バージョン管理システムを用いた場合，
片方のバージョンに存在する共通部分に関する不具合修正を含む変更のみを，
他方のバージョンに適用する方法が用意されている。


