# Movie Exporter for Shade3D

Shade3Dのアニメーションレンダリングを、mp4(H.264)またはwebm(VP8/VP9)形式で出力するプラグインです。    

本プラグインは動画出力でOpenCV 4.3.0 ( https://opencv.org/ )を使用しています。    

## 起動方法

Movie Exporter for Shade3Dプラグインは、OpenCVの動的ライブラリを参照します。    

### Windows環境の場合

OpenCVを「C:\WinApp\opencv-4.3.0」に展開した場合、以下のようなバッチファイルを作成し
Shade3Dをバッチから起動します。    

    set OPENCV_PATH=C:\WinApp\OpenCV-4.3.0
    set PATH=%OPENCV_PATH%\build\x64\vc15\bin;%PATH%
    
    set Shade3D_APP=C:\Program Files\Shade3D\Shade3D ver.17
    "%Shade3D_APP%\bin\shade.exe"

この場合、「C:\WinApp\opencv-4.3.0\build\x64\vc15\bin」内の「opencv_videoio_ffmpeg430_64.dll」「opencv_world430.dll」の2つの動的ライブラリが    
Shade3D実行時に参照されます。    
「set PATH」の行で検索パスを追加し、「"%Shade3D_APP%\bin\shade.exe"」の行でShade3D ver.17を実行しています。    
OpenCVのインストールフォルダ、Shade3Dのインストールフォルダは環境によって変わります。    
「OPENCV_PATH」にOpenCV 4.3.0のインストールフォルダ、「Shade3D_APP」にShade3Dのインストールフォルダを指定するようにしてください。    

### Mac環境の場合

