/**
 * 動画ファイルをエクスポートする.
 */
#include "ExportMovieWithOpenCV.h"

/*
参考 : 
	http://shibafu3.hatenablog.com/entry/2016/11/13/151118
	https://blog.shikoan.com/opencv-h264/
*/

CExportMovieWithOpenCV::CExportMovieWithOpenCV ()
{
}

CExportMovieWithOpenCV::~CExportMovieWithOpenCV ()
{
	clear();
}

void CExportMovieWithOpenCV::clear ()
{
	m_viderWriter.reset();
	m_imgD.release();
}

/**
 * 初期化処理.
 * @param[in] movieData  動画の情報.
 * @param[in] fileName   出力ファイル名。拡張子はmp4であること.
 * @param[in] frameRate  フレームレート.
 * @param[in] frameSize  フレームサイズ.
 */
bool CExportMovieWithOpenCV::init (const MovieData::CMovieData& movieData, const std::string& fileName, const int frameRate, const sx::vec<int,2> frameSize)
{
	m_width  = frameSize.x;
	m_height = frameSize.y;

	int fourcc = 0;
	if (movieData.movieType == MovieData::MOVIE_TYPE::movie_type_mp4) {
		// CODECでH264を指定。この場合、openh264がいるらしいがなくても動作した.
		fourcc = cv::VideoWriter::fourcc('H','2','6','4');
		//fourcc = cv::VideoWriter::fourcc('H','E','V','C');		// H.265
	} else {
		if (movieData.webmCodec == MovieData::WEBM_CODEC_TYPE::webm_codec_vp8) {
			fourcc = cv::VideoWriter::fourcc('V','P','0','8');
		} else {
			fourcc = cv::VideoWriter::fourcc('V','P','0','9');
		}
	}
	if (fourcc == 0) return false;

	m_viderWriter.reset(new cv::VideoWriter(fileName.c_str(), fourcc, (float)frameRate, cv::Size(m_width, m_height)));
	if (!m_viderWriter->isOpened()) return false;

	// RGB 24 bitのバッファを作成.
	m_imgD.create(cv::Size(m_width, m_height), CV_8UC3);

	return true;
}

/**
 * 破棄処理.
 */
void CExportMovieWithOpenCV::term ()
{
	// m_viderWriterを解放することでファイルが閉じられる状態になる.
	clear();
}

/**
 * 1フレーム分を出力.
 */
void CExportMovieWithOpenCV::addImage (sxsdk::image_interface* image)
{
	try {
		// imageの画像をm_imgDに格納.
		std::vector<sx::rgba8_class> lines;
		lines.resize(m_width);

		int iPos = 0;
		const int widSize = m_width * 3;

		for (int y = 0; y < m_height; ++y) {
			int iPos2 = iPos;
			image->get_pixels_rgba(0, y, m_width, 1, &(lines[0]));
			for (int x = 0; x < m_width; ++x) {
				*(m_imgD.data + iPos2 + 0) = lines[x].blue;
				*(m_imgD.data + iPos2 + 1) = lines[x].green;
				*(m_imgD.data + iPos2 + 2) = lines[x].red;
				iPos2 += 3;
			}
			iPos += widSize;
		}

		// OpenCVにm_imgDを格納.
		(*m_viderWriter) << m_imgD;

	} catch (...) { }
}

