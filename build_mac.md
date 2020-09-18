# ビルド方法 (Mac)

プラグインのビルドは、Xcode 10.1を使用しました。    

## OpenCVのインストール

「[起動方法 (Mac)](./setup_mac.md) 」の手順でOpenCVをMac環境にインストールしておきます。    

## Shade3DプラグインSDKでのプロジェクトとして配置


## Xcodeでビルド

Xcodeで「MovieExporter/mac/plugins/Template.xcodeproj」を開きます。    

OpenCVの検索パスとして、以下を参照しています。    

ヘッダの検索パス : /usr/local/include/opencv4    
ライブラリの検索パス : /usr/local/lib     

ライブラリは「libopencv_xxxx」のものがOpenCV関連のファイルです。    


