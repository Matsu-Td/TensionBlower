
/**
 * @file TitleBGM.cpp
 * @brief アウトゲーム用BGM再生
 *
 * @date 2021-02-13
 */

#include "TitleBGM.h"
#include "Sound.h"

TitleBGM::TitleBGM() {
	// BGM再生開始
	PlaySoundMem(gSound._bgm["titlebgm"], DX_PLAYTYPE_BACK);
}

TitleBGM::~TitleBGM() {
	// BGM再生停止
	StopSoundMem(gSound._bgm["titlebgm"]);
}