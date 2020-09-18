# 起動方法 (Mac)

Mac環境での「Movie Exporter for Shade3D」の起動方法です。     
OpenCVを使用しています。Mac環境にOpenCVをインストールする必要があります。    

## Homebrewのインストール

Macでパッケージをインストールするツールとして「Homebrew」というのがあります。    
これを使用して、あらかじめOSにHomebrewをインストールします。    
Homebrewについては以下を参照してくださいませ。    

https://brew.sh/index_ja

### Homebrewが既にインストールされているかチェック

コマンドラインで操作するため、「ターミナル」（アプリケーション/ユーティリティ内）を起動します。     

    which brew

で「/usr/local/bin/brew」のように表示されれば、すでにHomebrewはインストールされています。    

## OpenCVのインストール

コマンドラインで操作するため、「ターミナル」（アプリケーション/ユーティリティ内）を起動します。     

    brew list --versions | grep opencv

を実行し、OpenCVが既にインストールされておりバージョンが4.xである場合は新たにOpenCVをインストール必要はありません。    
存在しない場合は、以下でバージョン4系の最新のOpenCVをインストールします。    

    brew install opencv@4

brewのアップデートを促される場合は、以下でbrewをアップデートしてください。    

    brew update

これらのインストール処理は時間がかかります。     

    brew list --versions | grep opencv

で、OpenCVのバージョンを再度確認します。    
「opencv 4.4.0_2」のように表示されれば正しくインストールされています(4系ですとどれでもいいです)。    

## プラグインをpluginsフォルダに複製

Shade3Dのpluginsフォルダ（/Users/ユーザ名/Documents/Shade3D/Shade3D ver.17/plugins など）に「MovieExporter.shdplugin」を複製します。    

## Shade3Dを起動

Shade3Dを起動し、メインメニューの「レンダリング」-「アニメーション」を選択したときに    
ファイルダイアログボックスの「ムービー」で「mp4」「webm」が選択できるようになっているのを確認してください。     


