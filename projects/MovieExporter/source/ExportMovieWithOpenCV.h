/**
 * 動画ファイルをエクスポートする.
 */
#ifndef _EXPORT_MOVIE_H
#define _EXPORT_MOVIE_H

#include "GlobalHeader.h"
#include "MovieData.h"

#include "opencv2/Videoio.hpp"
#include "opencv2/core.hpp"

class CExportMovieWithOpenCV
{
private:

private:
	std::unique_ptr<cv::VideoWriter> m_viderWriter;
	cv::Mat m_imgD;
	int m_width, m_height;

public:
	CExportMovieWithOpenCV ();
	~CExportMovieWithOpenCV ();

	void clear ();

	/**
	 * 初期化処理.
	 * @param[in] movieData  動画の情報.
	 * @param[in] fileName   出力ファイル名。拡張子はmp4であること.
	 * @param[in] frameRate  フレームレート.
	 * @param[in] frameSize  フレームサイズ.
	 */
	bool init (const MovieData::CMovieData& movieData, const std::string& fileName, int frameRate = 30, const sx::vec<int,2> frameSize = sx::vec<int,2>(400, 300));

	/**
	 * 破棄処理.
	 */
	void term ();

	/**
	 * 1フレーム分を出力.
	 */
	void addImage (sxsdk::image_interface* image);

};

#endif

