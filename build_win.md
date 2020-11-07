# ビルド方法

## Windows

プラグインのビルドは、Visual Studio 2017でC++を使いました。    

## OpenCVのインストール

「[起動方法 (Win)](./setup_win.md) 」の手順でOpenCVをWindows環境に展開しておきます。    

「C:\WinApp\OpenCV-4.5.0」に解凍した場合、以下のような構成になっているのを確認します。    

    [OpenCV-4.5.0]
        [build]
          [bin]
          [etc]
          [include]  ← ヘッダファイル
          [java]
          [python]
          [x64]
            [vc14]
            [vc15]
              [bin]  ← 実行時に必要な動的ライブラリ
              [lib]  ← 使用する静的ライブラリ
          LICENSE
        [sources]
        LICENSE.txt
※ 末端は省略しています。    

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

「win_vs2017」がVC++2017用のプロジェクトです。    
このフォルダ内の「MovieExporter.sln」が起動プロジェクトになります。    

## VC++2017のプロジェクトでの指定

OpenCVの検索パスとして、以下を参照しています。    

* ヘッダの検索パス : OpenCV-4.5.0/include    
* ライブラリの検索パス : OpenCV-4.5.0/build/x64/vc15/lib     

「OpenCV-4.5.0」はOpenCVの展開先のフォルダです。    

VC++2017のプロジェクトで、OpenCVのヘッダとライブラリを検索できるように指定を確認します。   

ソリューションエクスプローラの「MovieExporter」を右クリックし、プロパティを選択します。    

「C/C++」の「全般」の「追加のインクルードディレクトリ」で「C:\WinApp\OpenCV-4.5.0\build\include」となっている箇所がOpenCVのヘッダのパスになります。    
環境に合わせて書き換えるようにしてください。    

「リンカー」の「全般」の「追加のライブラリディレクトリ」で
「C:\WinApp\OpenCV-4.5.0\build\x64\vc15\lib」となっている箇所がOpenCVのライブラリのパスになります。    
環境に合わせて書き換えるようにしてください。    

「リンカー」の「入力」の「追加の依存ファイル」で    
Debug時は「opencv_world450d.lib」、Release時は「opencv_world450.lib」を指定します。     

以上でビルドすると、「MovieExporter64.dll」が生成されます。    


