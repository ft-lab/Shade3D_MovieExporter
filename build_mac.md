# ビルド方法 (Mac)

プラグインのビルドは、Xcode 10.1を使用しました。    

## OpenCVのインストール

「[起動方法 (Mac)](./setup_mac.md) 」の手順でOpenCVをMac環境にインストールしておきます。    

## Shade3DプラグインSDKでのプロジェクトとして配置

Shade3DプラグインSDKをダウンロードします。    
Shade3D_MovieExporter/projects/MovieExporterフォルダをShade3DのプラグインSDKのplugin_projectsフォルダに複製します。    

以下のような配置になります。    

    [shade 15 Plugin SDK]
        [plugin_projects]
            [MovieExporter]
                [mac]
                [source]
                [win_vs2017]

「mac」がXcode用のプロジェクトです。    
このフォルダ内の「plugins/Template.xcodeproj」が起動プロジェクトになります。    

## Xcodeでビルド

Xcodeで「MovieExporter/mac/plugins/Template.xcodeproj」を開きます。    

OpenCVの検索パスとして、以下を参照しています。    

* ヘッダの検索パス : /usr/local/include/opencv4    
* ライブラリの検索パス : /usr/local/lib     

ライブラリは「libopencv_xxxx」のものがOpenCV関連のファイルです。    

まだ途中,,,


