/**
 * @file   TitleBGM.cpp
 * @brief  アウトゲーム用BGM再生処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/13
 */

#include "TitleBGM.h"
#include "../Sound/Sound.h"

using namespace tensionblower::mode;

TitleBGM::TitleBGM() {
	// BGM再生開始
	PlaySoundMem(gSound._bgm["titlebgm"], DX_PLAYTYPE_LOOP);
}

TitleBGM::~TitleBGM() {
	// 何もしない
}