/**
 * @file   PlayerVoice.cpp
 * @brief  プレイヤー声優 声データ読み込み処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "PlayerVoice.h"

// 実体：声データ呼び出し
PlayerVoice gPlayerVoice;

/*
 * 声データ読み込み
 */
int PlayerVoice::LoadVoice(const TCHAR* filePath) {
	return ResourceServer::LoadSoundMem(filePath);
}

/*
 * 声データ読み込み
 */
void PlayerVoice::Initialize() {

	_vc["clear"]     = LoadVoice("res/voice/player/clear.wav");
	_vc["gameover"]  = LoadVoice("res/voice/player/gameover.wav");
	_vc["gamestart"] = LoadVoice("res/voice/player/gamestart.wav");
	_vc["hidan"]     = LoadVoice("res/voice/player/hidan.wav");
	_vc["hukki"]     = LoadVoice("res/voice/player/hukki.wav");
	_vc["ikuzo"]     = LoadVoice("res/voice/player/ikuzo.wav");
	_vc["strong"]    = LoadVoice("res/voice/player/strong3.wav");
	_vc["title"]     = LoadVoice("res/voice/player/title.wav");
	_vc["weak1"]     = LoadVoice("res/voice/player/weak1.wav");
	_vc["weak2"]     = LoadVoice("res/voice/player/weak2.wav");
	_vc["weak3"]     = LoadVoice("res/voice/player/weak3.wav");
	_vc["weak4"]     = LoadVoice("res/voice/player/weak4.wav");
}
