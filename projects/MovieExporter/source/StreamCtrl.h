/**
 * streamの読み込み/保存.
 */
#ifndef _STREAMCTRL_H
#define _STREAMCTRL_H

#include "GlobalHeader.h"
#include "MovieData.h"

namespace StreamCtrl
{
	/**
	 * 動画オプションを保存.
	 */
	void saveMovieData (sxsdk::scene_interface* scene, const MovieData::CMovieData& data);

	/**
	 * 動画オプションを読み込み.
	 */
	bool loadMovieData (sxsdk::scene_interface* scene, MovieData::CMovieData& data);

};

#endif
