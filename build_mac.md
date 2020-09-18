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

OpenCVのインストールは決められた「/usr/local」にインストールされるため、Xcodeでそのままビルドすると「MovieExporter.shdplugin」が生成されます。    

プロジェクト上でOpenCVを参照するために以下を指定しました。   

### Frameworks and Librabies

以下を追加しました。    
「/usr/local/lib」に配置されているdylibです。    
Finderのメニューより「移動」-「フォルダへ移動」を選択し、
「/usr/local/lib」を開いてXcodeの「Frameworks and Librabies」にドラッグしました。    

* libopencv_core.dylib
* libopencv_videoio.dylib
* libopencv_imgcodecs.dylib
* libopencv_imgproc.dylib

### Build Settings

プロジェクトの「MovieExporter」の「Build Settings」で    

「Header Search Paths」に「/usr/local/include/opencv4」を追加。    
「Library Search Paths」に「/usr/local/lib」を追加。    

## OpenCVのヘッダを修正

Xcode 10.1 + OpenCV 4.4.0_2ではOpenCVのビルドエラーが出ていました。     
以下を書き換えました。    


### /usr/local/include/opencv4/opencv2/core/mat.hpp

「FIXED_TYPE = 0x8000 << KIND_SHIFT」のint範囲オーバー。    
以下に書き換え。    

    FIXED_TYPE = (unsigned int)0x8000 << KIND_SHIFT,

### /usr/local/include/opencv4/opencv2/videoio.hpp

「enum { CAP_OPENNI_DEPTH_GENERATOR = 1 << 31,」のint範囲オーバー。    
以下に書き換え。    

    enum { CAP_OPENNI_DEPTH_GENERATOR = (unsigned int)1 << 31,

### /usr/local/include/opencv4/opencv2/core.hpp

「virtual ~Exception() throw();」のthrowでエラー。    
以下に書き換え。    

    virtual ~Exception() noexcept;

「virtual const char *what() const throw() CV_OVERRIDE;」のthrowでエラー。    
以下に書き換え。    

     virtual const char *what() const noexcept CV_OVERRIDE;

