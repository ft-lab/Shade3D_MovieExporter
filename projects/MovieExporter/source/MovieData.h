/**
 *  動画ファイルのオプション情報.
 */

#ifndef _MOVIEDATA_H
#define _MOVIEDATA_H

#include "GlobalHeader.h"

namespace MovieData
{
	/**
	 * 動画ファイルの種類.
	 */
	enum MOVIE_TYPE {
		movie_type_mp4 = 0,		// mp4形式.
		movie_type_webm,		// webm形式.
	};

	/**
	 * mp4のCODECの種類.
	 */
	enum MP4_CODEC_TYPE {
		mp4_codec_h264 = 0,			// H.264.
		mp4_codec_h265,				// H.265 (OpenCVではうまくいかないので未使用).
	};

	/**
	 * webmのCODECの種類.
	 */
	enum WEBM_CODEC_TYPE {
		webm_codec_vp8 = 0,			// VP8.
		webm_codec_vp9,				// VP9.
	};

	/**
	 * 動画出力時のオプション.
	 */
	class CMovieData
	{
	public:
		MOVIE_TYPE movieType;			// 動画の種類.
		MP4_CODEC_TYPE mp4Codec;		// mp4使用時のCODEC.
		WEBM_CODEC_TYPE webmCodec;		// webm使用時のCODEC.

	public:
		CMovieData ();
		CMovieData (const CMovieData& v);
		~CMovieData ();

		CMovieData& operator = (const CMovieData &v) {
			this->movieType  = v.movieType;
			this->mp4Codec   = v.mp4Codec;
			this->webmCodec  = v.webmCodec;
			return (*this);
		}

		void clear ();
	};
}

#endif
