/**
 * @file   TitleBGM.cpp
 * @brief  アウトゲーム用BGM再生
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "TitleBGM.h"
#include "Sound.h"

TitleBGM::TitleBGM() {
	// BGM再生開始
	PlaySoundMem(gSound._bgm["titlebgm"], DX_PLAYTYPE_BACK);
}

TitleBGM::~TitleBGM() {

}