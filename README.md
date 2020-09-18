# Movie Exporter for Shade3D

Shade3Dのアニメーションレンダリングを、mp4(H.264)またはwebm(VP8/VP9)形式で出力するプラグインです。    

本プラグインは動画出力でOpenCV 4.4.0 ( https://opencv.org/ )を使用しています。    

## 機能

以下の機能があります。    

* アニメーションレンダリングで、「mp4」(H.264)で出力。    
* アニメーションレンダリングで、「webm」(VP8/VP9)で出力。    

## 動作環境

* Windows 7/8/10以降のOS
* macOS 10.11以降
* Shade3D ver.14以降で、Standard/Professional版（Basic版では動作しません）
* Shade3Dの64bit版のみで使用できます。32bit版のShade3Dには対応していません。

## 起動方法

### プラグインダウンロード

以下からプラグインの最新版をダウンロードしてください。     

https://github.com/ft-lab/Shade3D_MovieExporter/releases

Movie Exporter for Shade3Dプラグインは、OpenCVの動的ライブラリを参照します。    
起動方法はWindows/Macで異なります。    

### Windows環境の場合

[起動方法 (Windows)](./setup_win.md) をご参照くださいませ。    


### Mac環境の場合

[起動方法 (Mac)](./setup_mac.md) をご参照くださいませ。    

## 使い方

Shade3Dを起動し、任意のシーンをアニメーションレンダリングします。    
メインメニューの「レンダリング」-「アニメーションレンダリング」を選択し、ファイルダイアログボックスで「ファイルの種類」を「mp4」またはwebm」を選択します。    
mp4の場合は、CODECは「H.264」のみです。    
webmの場合は、CODECとして「VP8」または「VP9」を選択できます。    
4K以上の解像度でアニメーションレンダリングしたい場合は「webm」で「VP9」を選択するようにしてください。     

## 制限事項

* オーディオ情報は出力されません。    

## ビルド方法 (開発者向け)

プラグインのビルド方法です。    

* [ビルド方法 (Windows)](./build_win.md)
* [ビルド方法 (Mac)](./build_mac.md)

## ライセンス

This software is released under the MIT License, see [LICENSE](./LICENSE).    

### OpenCVのライセンス

OpenCVは「3-clause BSD License」になります。    
https://opencv.org/license/    

### H.264のライセンス

「Movie Exporter for Shade3D」では、OpenCVの機能を使用してmp4(CODECはH.264)形式の出力を行っています。    
本プラグインではH.264にはタッチしていません。    
OpenCVでは、Windows版のmp4(H.264)エクスポートで「Microsoft Media Foundation (MSMF)」を使用しているようです。    
この場合は特にライセンスはOpenCV側では問われないようです。    

H.264を使用している場合の出力動画の使用については、使い方によってはエンドユーザーとしてのライセンスが必要になる場合があります。    
"AVC Patent Portfolio License" ( https://www.mpegla.com/programs/avc-h-264/license-agreement/ )も参照するようにしてください。    

## 更新履歴

### [2020/09/18] ver.1.0.0.0

* 初回バージョン

