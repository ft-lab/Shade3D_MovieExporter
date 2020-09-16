/**
 * streamの読み込み/保存.
 */
#include "StreamCtrl.h"

/**
 * 動画オプションを保存.
 */
void StreamCtrl::saveMovieData (sxsdk::scene_interface* scene, const MovieData::CMovieData& data)
{
	try {
		compointer<sxsdk::stream_interface> stream(scene->create_attribute_stream_interface_with_uuid(MOVIE_DATA_ATTRIBUTE_ID));
		if (!stream) return;

		stream->set_size(0);
		stream->set_pointer(0);

		int iDat;
		int iVersion = MOVIE_DATA_STREAM_VERSION;
		stream->write_int(iVersion);

		iDat = (int)data.movieType;
		stream->write_int(iDat);

		iDat = (int)data.mp4Codec;
		stream->write_int(iDat);

		iDat = (int)data.webmCodec;
		stream->write_int(iDat);

	} catch (...) { }
}


/**
 * 動画オプションを読み込み.
 */
bool StreamCtrl::loadMovieData (sxsdk::scene_interface* scene, MovieData::CMovieData& data)
{
	data.clear();

	try {
		compointer<sxsdk::stream_interface> stream(scene->get_attribute_stream_interface_with_uuid(MOVIE_DATA_ATTRIBUTE_ID));
		if (!stream) return false;

		stream->set_pointer(0);

		int iDat;
		int iVersion;
		stream->read_int(iVersion);

		stream->read_int(iDat);
		data.movieType = (MovieData::MOVIE_TYPE)iDat;

		stream->read_int(iDat);
		data.mp4Codec = (MovieData::MP4_CODEC_TYPE)iDat;

		stream->read_int(iDat);
		data.webmCodec = (MovieData::WEBM_CODEC_TYPE)iDat;

		return true;

	} catch (...) { }

	return false;
}

