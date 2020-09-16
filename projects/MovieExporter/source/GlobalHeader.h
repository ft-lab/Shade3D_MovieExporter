/**
 *  @file   GlobalHeader.h
 *  @brief  共通して使用する変数など.
 */

#ifndef _GLOBALHEADER_H
#define _GLOBALHEADER_H

#include "sxsdk.cxx"

/**
 * プラグインインターフェイス派生クラスのプラグインID.
 */
#define MOVIE_IMAGE_EXPORTER_ID sx::uuid_class("42198A74-8540-4B79-9C3D-DE249BEDF2AD")

// sceneに保持する動画情報のUUID.
#define MOVIE_DATA_ATTRIBUTE_ID sx::uuid_class("3BF677D2-4B0D-4B70-92CB-5E60A91A30A1")

// 動画情報のstreamバージョン.
#define MOVIE_DATA_STREAM_VERSION		0x100


#endif
