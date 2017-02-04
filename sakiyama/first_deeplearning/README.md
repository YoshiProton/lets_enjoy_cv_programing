書籍　はじめての深層学習プログラミングのお勉強


#最初の環境の構築
* 各環境ごとのDockerのインストール方法を参照
* 次のシェルを実行
```
docker pull sakiyamak/deel
./run_docker.sh
```
* http://localhost:8888/ にアクセス
* jupyterのターミナルを実行して次のシェルを実行
```
cd /root/deel/data
./getCaltech101.sh
cp -r /root/deel/data /root/prgm
cd /root/deel/misc
./getPretrainedModels.sh
cp -r /root/deel/misc /root/prgm
cp -r /root/deel/cache /root/prgm
```

#2回目以降の実行の仕方
```
./run_docker.sh
```
* 起動後に「http://localhost:8888/」 にアクセス


#環境の変更
```
#1をつけると直接dockerにログイン
./run_docker.sh 1
```

#環境の説明
* docker sakiyamak/deel
* conda env deel
* jupyterで実行