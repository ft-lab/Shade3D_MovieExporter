# 起動方法 (Windows)

Windows環境での「Movie Exporter for Shade3D」の起動方法です。     
OpenCVを使用しているため、Shade3Dプラグインとして実行する場合にOpenCVの動的ライブラリを検索できるようにする必要があります。    

## OpenCVのインストール

OpenCVのReleasesページ ( https://opencv.org/releases/ )より、    
「OpenCV – 4.4.0」のWindows版をダウンロードし、解凍します。    
バージョンが大事です。Movie Exporter for Shade3Dでは OpenCV ver.4.4.0を使用しています。    

「C:\WinApp\OpenCV-4.4.0」に解凍した場合、以下のような構成になっているのを確認します。    

    [OpenCV-4.4.0]
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

## プラグインをpluginsフォルダに複製

Shade3Dのpluginsフォルダ（/Users/ユーザ名/Documents/Shade3D/Shade3D ver.17/plugins など）に「MovieExporter.shdplugin」を複製します。    
プラグイン本体の「MovieExporter64.dll」をShade3Dのpluginsフォルダにコピーします。    
Shade3D ver.17の場合は、初期状態では「C:\Users\ユーザ名\Documents\Shade3D\Shade3D ver.17\plugins」がpluginsフォルダになります。    

## Shade3Dを起動

OpenCVを「C:\WinApp\OpenCV-4.4.0」に展開した場合、以下のようなバッチファイルを作成し
Shade3Dをバッチから起動します。    
このファイルはサンプルとして「run_shade3d_v17_with_OpenCV.bat」をご参照くださいませ。    

    set OPENCV_PATH=C:\WinApp\OpenCV-4.4.0
    set PATH=%OPENCV_PATH%\build\x64\vc15\bin;%PATH%
    
    set Shade3D_APP=C:\Program Files\Shade3D\Shade3D ver.17
    "%Shade3D_APP%\bin\shade.exe"

この場合、「C:\WinApp\OpenCV-4.4.0\build\x64\vc15\bin」内の「opencv_videoio_ffmpeg440_64.dll」「opencv_videoio_msmf440_64.dll」「opencv_world440.dll」の3つの動的ライブラリが    
Shade3D実行時に参照されます。    
「set PATH」の行で検索パスを追加し、「"%Shade3D_APP%\bin\shade.exe"」の行でShade3D ver.17を実行しています。    
OpenCVのインストールフォルダ、Shade3Dのインストールフォルダは環境によって変わります。    
「OPENCV_PATH」にOpenCV 4.4.0のインストールフォルダ、「Shade3D_APP」にShade3Dのインストールフォルダを指定するようにしてください。    

上記バッチファイル経由でShade3Dを起動し、メインメニューの「レンダリング」-「アニメーション」を選択したときに    
ファイルダイアログボックスの「ファイルの種類」で「mp4」「webm」が選択できるようになっているのを確認してください。     

## バッチを作らずに使用したい場合

上記のようなバッチファイルを使用せずにMovie Exporter for Shade3Dを使用したい場合は、    
OpenCV 4.4.0の動的ライブラリ (build\x64\vc15\bin内)「opencv_videoio_ffmpeg440_64.dll」「opencv_videoio_msmf440_64.dll」「opencv_world440.dll」を管理者権限で、    
Shade3Dの実行ファイルのフォルダ（ver.17の場合は C:\Program Files\Shade3D\Shade3D ver.17\bin）に複製するようにしてください。     


