/**
 * MP4/webm形式の動画ファイルをエクスポート.
 */
#include "MovieImageExporterInterface.h"
#include "StreamCtrl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 作業用のディレクトリ名.
#define TEMP_MOVIE_DIR_NAME "__shade3d_movie_2020"

// ダイアログボックスのパラメータ.
enum {
	dlg_group_id = 1000,						// グループ.

	dlg_mp4_codec_id = 101,						// mp4でのCODEC選択.
	dlg_webm_codec_id = 201,					// webmでのCODEC選択.
};

CMovieImageExporterInterface::CMovieImageExporterInterface (sxsdk::shade_interface& shade) : shade(shade)
{
	m_frame = 0;
	m_tempDirPath = "";
	m_tempFilePath = "";
	m_exportFilePath = "";
	m_criticalScetion = shade.create_critical_section_interface();
	m_stream = NULL;
}

CMovieImageExporterInterface::~CMovieImageExporterInterface ()
{
}

const char *CMovieImageExporterInterface::get_file_extension (int index, void*)
{
	if (index == 0) { return "mp4"; }
	if (index == 1) { return "webm"; }

	return NULL;
}

const char *CMovieImageExporterInterface::get_file_description (int index, void*)
{
	if (index == 0) { return "mp4"; }
	if (index == 1) { return "webm"; }
	return NULL;
}

/**
 * アプリケーション終了時に呼ばれる.
 */
void CMovieImageExporterInterface::cleanup (void *)
{
	// 作業用ディレクトリを削除.
	// 作業フォルダは、shade.get_temporary_path()で与えた後に削除すると、.
	// アプリ内では再度作業フォルダを作成できない。そのため、removeはアプリ終了時に呼んでいる.
	m_tempDirPath  = std::string(shade.get_temporary_path(TEMP_MOVIE_DIR_NAME));
	shade.remove_directory_and_files(m_tempDirPath.c_str());
}

/**
 * レンダリング前に呼ばれる.
 */
bool CMovieImageExporterInterface::do_pre_export (int index, sxsdk::image_interface *image, void*)
{
	m_frame = 0;

	// 動画の種類.
	MovieData::MOVIE_TYPE movieType = (index == 0) ? MovieData::MOVIE_TYPE::movie_type_mp4 : MovieData::MOVIE_TYPE::movie_type_webm;

	// レンダリング情報を取得.
	compointer<sxsdk::scene_interface> scene(shade.get_scene_interface());

	const int width  = image->get_size().x;
	const int height = image->get_size().y;
	int frameRate = 30;
	try {
		if (scene) {
			frameRate = scene->get_frame_rate();
		}
	} catch (...) { }

	// 動画オプションダイアログボックスを表示.
	if (scene) {
		compointer<sxsdk::dialog_interface> dlg(shade.create_dialog_interface_with_uuid(MOVIE_IMAGE_EXPORTER_ID));
		dlg->set_resource_name("movieData_dlg");
		dlg->set_responder(this);
		this->AddRef();

		StreamCtrl::loadMovieData(scene, m_data);
		m_data.movieType = movieType;
		if (!dlg->ask()) return false;

		StreamCtrl::saveMovieData(scene, m_data);
	}

	// 作業用のファイル名.
	m_tempDirPath  = std::string(shade.get_temporary_path(TEMP_MOVIE_DIR_NAME));
	m_tempFilePath = m_tempDirPath;
	
	if (movieType == MovieData::MOVIE_TYPE::movie_type_mp4) m_tempFilePath += std::string("/xxx.mp4");
	else if (movieType == MovieData::MOVIE_TYPE::movie_type_webm) m_tempFilePath += std::string("/xxx.webm");

	// mp4出力の初期化.
	m_criticalScetion->enter();
	m_exportMovie.reset(new CExportMovieWithOpenCV());
	const bool ret = m_exportMovie->init(m_data, m_tempFilePath, frameRate, sx::vec<int,2>(width, height));
	m_criticalScetion->leave();
	if (!ret) {
		m_exportMovie.reset();
		shade.message("--- Movie Exporter ---");
		shade.message(shade.gettext("msg_error_VideoOutputFailed"));
	}

	m_exportFilePath = "";

	return ret;
}

/**
 * 1フレームごとのエクスポート.
 */
bool CMovieImageExporterInterface::do_export (int index, sxsdk::image_interface *image, sxsdk::stream_interface *stream, void*)
{
	if (stream && m_exportFilePath == "") {
		m_exportFilePath = std::string(stream->get_file_path());
		m_stream = stream;
	}

	// 動画の画像を追加.
	m_criticalScetion->enter();
	m_exportMovie->addImage(image);
	m_criticalScetion->leave();

	m_frame++;

	return true;
}

/**
 * エクスポートを行った後（アニメーション時の最後の1回）に呼ばれる.
 */
bool CMovieImageExporterInterface::do_post_export (int index, sxsdk::image_interface *image, void*)
{
	// 動画の格納終了.
	m_criticalScetion->enter();
	m_exportMovie->term();
	m_criticalScetion->leave();

	// ファイルを複製する.
	if (m_tempFilePath != "" && m_exportFilePath != "") {
		try {
			shade.copy_file(m_tempFilePath.c_str(), m_exportFilePath.c_str());

		} catch (...) { }
	}

	return true;
}


//--------------------------------------------------.
//  ダイアログのイベント処理用.
//--------------------------------------------------.
/**
 * ダイアログの初期化.
 */
void CMovieImageExporterInterface::initialize_dialog (sxsdk::dialog_interface &d, void *)
{
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_group_id));

		int groupIndex = 0;
		switch (m_data.movieType) {
		case MovieData::MOVIE_TYPE::movie_type_mp4:
			groupIndex = 0;
			break;
		case MovieData::MOVIE_TYPE::movie_type_webm:
			groupIndex = 1;
			break;
		}
		item->set_selection(groupIndex);
	}
}

/** 
 * ダイアログのイベントを受け取る.
 */
bool CMovieImageExporterInterface::respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void *)
{
	const int id = item.get_id();		// アクションがあったダイアログアイテムのID.

	if (id == sx::iddefault) {
		MovieData::MOVIE_TYPE type = m_data.movieType;
		m_data.clear();
		m_data.movieType = type;

		load_dialog_data(d);
		return true;
	}

	if (id == dlg_mp4_codec_id) {
		m_data.mp4Codec = (MovieData::MP4_CODEC_TYPE)item.get_selection();
		return true;
	}

	if (id == dlg_webm_codec_id) {
		m_data.webmCodec = (MovieData::WEBM_CODEC_TYPE)item.get_selection();
		return true;
	}

	return false;
}

/**
 * ダイアログのデータを設定する.
 */
void CMovieImageExporterInterface::load_dialog_data (sxsdk::dialog_interface &d, void *)
{
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_mp4_codec_id));
		item->set_selection((int)m_data.mp4Codec);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_webm_codec_id));
		item->set_selection((int)m_data.webmCodec);
	}

	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_group_id));

		int groupIndex = 0;
		switch (m_data.movieType) {
		case MovieData::MOVIE_TYPE::movie_type_mp4:
			groupIndex = 0;
			break;
		case MovieData::MOVIE_TYPE::movie_type_webm:
			groupIndex = 1;
			break;
		}

		if (item->get_selection() != groupIndex) {
			item->set_selection(groupIndex);
		}
	}
}

