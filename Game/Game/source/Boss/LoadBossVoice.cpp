/**
 * @file   LoadBossVoice.cpp
 * @brief  �{�X���D ���f�[�^�ǂݍ��ݏ���
 *
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "LoadBossVoice.h"

using namespace tensionblower::boss;

 // ���́F���f�[�^�Ăяo��
LoadBossVoice gBossVoice;

int LoadBossVoice::LoadVoice(const TCHAR* filePath) {
	return ResourceServer::LoadSoundMem(filePath);
}

/*
 * ���f�[�^�ǂݍ���
 */
void LoadBossVoice::Initialize() {

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
