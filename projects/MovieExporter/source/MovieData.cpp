/**
 *  動画ファイルのオプション情報.
 */

#include "MovieData.h"

using namespace MovieData;


CMovieData::CMovieData ()
{
	clear();
}

CMovieData::CMovieData (const CMovieData& v)
{
	this->movieType  = v.movieType;
	this->mp4Codec   = v.mp4Codec;
	this->webmCodec  = v.webmCodec;
}

CMovieData::~CMovieData ()
{
}

void CMovieData::clear ()
{
	movieType = MOVIE_TYPE::movie_type_mp4;
	mp4Codec  = MP4_CODEC_TYPE::mp4_codec_h264;
	webmCodec = WEBM_CODEC_TYPE::webm_codec_vp8;
}

