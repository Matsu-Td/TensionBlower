/**
 * @file   BossVoice.cpp
 * @brief  ボス声優 声データ読み込み
 *
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "BossVoice.h"

 // 実体：声データ呼び出し
BossVoice gBossVoice;

int BossVoice::LoadVoice(const TCHAR* filePath) {
	return ResourceServer::LoadSoundMem(filePath);
}

/**
 * 声データ読み込み
 */
void BossVoice::Init() {

	_vc["attack1"] = LoadVoice("res/voice/boss/attack1.wav");
	_vc["attack2"] = LoadVoice("res/voice/boss/attack2.wav");
	_vc["attack3"] = LoadVoice("res/voice/boss/attack3.wav");
	_vc["attack4"] = LoadVoice("res/voice/boss/attack4.wav");
	_vc["attack5"] = LoadVoice("res/voice/boss/attack5.wav");
	_vc["attack6"] = LoadVoice("res/voice/boss/attack6.wav");
	_vc["gekiha"]  = LoadVoice("res/voice/boss/gekiha.wav");
	_vc["hidan"]   = LoadVoice("res/voice/boss/hidan.wav");
	_vc["hukki"]   = LoadVoice("res/voice/boss/hukki.wav");
	_vc["title"]   = LoadVoice("res/voice/boss/title.wav");
}
