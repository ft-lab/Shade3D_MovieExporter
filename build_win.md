# ビルド方法

## Windows

プラグインのビルドは、Visual Studio 2017を使用しC++を使いました。    

## OpenCVのインストール

「[起動方法 (Win)](./setup_win.md) 」の手順でOpenCVをWindows環境に展開しておきます。    

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

## Shade3DプラグインSDKでのプロジェクトとして配置

### VC++2017のプロジェクトでの指定

VC++2017で、    
ヘッダの検索パスに「opencv-4.3.0/include」を追加、
ライブラリの検索パスに「opencv-4.3.0/build/x64/vc15/lib」を追加します。    

TODO...

