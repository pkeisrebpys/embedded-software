# embedded-software 組み込みソフトウェア
組み込みソフトウェアを実装する上で必要となる知識をまとめる。
ソフトウェアを実行するハードウェアの知識から，
C言語でのソフトウェア実装についてまとめる。

本リポジトリの GitHub Pages へのリンクは次のとおり。
https://pkeisrebpys.github.io/embedded-software/

## ページ作成の方針
ページは本リポジトリの docs ディレクトリ以下に Markdown 形式で作成する。
作成した Markdown を GitHub Pages として公開する。

ページに挿入する図はベクター形式とし， svg をメインとする。
ラスター形式の場合は jpg もしくは png とする。
図は docs/images に保存し，本文から参照する。
図は git-lfs で管理する。
`*.svg`, `*.jpg`, `*.png` は git-lfs を通してリポジトリに追加する。

ページで参照する例題コードなどは `src` に保存する。

