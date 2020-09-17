/**
 * MP4/webm形式の動画ファイルをエクスポート.
 */

#ifndef _MOVIE_IMAGE_EXPORTER_INTERFACE_H
#define _MOVIE_IMAGE_EXPORTER_INTERFACE_H

#include "GlobalHeader.h"
#include "ExportMovieWithOpenCV.h"
#include "MovieData.h"

#include <memory>

struct CMovieImageExporterInterface : public sxsdk::image_exporter_interface
{
private:
	sxsdk::shade_interface& shade;
	int m_frame;

	std::unique_ptr<CExportMovieWithOpenCV> m_exportMovie;			// OpenCVを使った動画出力クラス.

	std::string m_tempDirPath;						// 作業用のディレクトリ名.
	std::string m_tempFilePath;						// 作業用のフルパス名.
	std::string m_exportFilePath;					// エクスポートするフルパスファイル名.

	compointer<sxsdk::critical_section_interface> m_criticalScetion;

	MovieData::CMovieData m_data;					// 動画オプション.

	bool m_needCopyFile;							// ファイルコピーの必要がある場合はtrue.

private:

	/**
	 * SDKのビルド番号を指定（これは固定で変更ナシ）。.
	 * ※ これはプラグインインターフェースごとに必ず必要。.
	 */
	virtual int get_shade_version () const { return SHADE_BUILD_NUMBER; }

	/**
	 * UUIDの指定（独自に定義したGUIDを指定）.
	 * ※ これはプラグインインターフェースごとに必ず必要。.
	 */
	virtual sx::uuid_class get_uuid (void * = 0) { return MOVIE_IMAGE_EXPORTER_ID; }

	/**
	 * アニメーション出力で使用.
	 */
	virtual bool accepts_animation (int index, void *aux=0) { return true; }

	virtual const char *get_file_extension (int index, void*);
	virtual const char *get_file_description (int index, void*);
	virtual bool do_pre_export (int index, sxsdk::image_interface *image, void*);
	virtual bool do_export (int index, sxsdk::image_interface *image, sxsdk::stream_interface *stream, void*);
	virtual bool do_post_export (int index, sxsdk::image_interface *image, void*);

	// use_custom_exportはShade3D本体から呼ばれない ?
	//virtual bool use_custom_export (int index, void *);
	//virtual bool do_export_custom (int index, sxsdk::image_interface* image, const std::string& path, sxsdk::scene_interface* scene, void*);

	/**
	 * idle時に定期的に呼ばれる.
	 */
	virtual void idle_task (bool &b, sxsdk::scene_interface *scene, void *aux=0);

	/**
	 * アプリケーション終了時に呼ばれる.
	 */
	virtual void cleanup (void *aux=0);

private:
	//--------------------------------------------------.
	//  ダイアログのイベント処理用.
	//--------------------------------------------------.
	/**
	 * ダイアログの初期化.
	 */
	virtual void initialize_dialog (sxsdk::dialog_interface &d, void * = 0);

	/** 
	 * ダイアログのイベントを受け取る.
	 */
	virtual bool respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void * = 0);

	/**
	 * ダイアログのデータを設定する.
	 */
	virtual void load_dialog_data (sxsdk::dialog_interface &d, void * = 0);

public:
	CMovieImageExporterInterface (sxsdk::shade_interface& shade);
	virtual ~CMovieImageExporterInterface ();

	/**
	 * プラグイン名をSXUL(text.sxul)より取得.
	 */
	static const char *name (sxsdk::shade_interface *shade) { return shade->gettext("movie_image_exporter_title"); }

};

#endif
