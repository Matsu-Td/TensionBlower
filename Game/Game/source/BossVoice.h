/**
 * @file   BossVoice.h
 * @brief  �{�X���D ���f�[�^�ǂݍ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/0$DAY
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

class BossVoice {
public:
	/**
	 * ���f�[�^�ǂݍ���
	 */
	void Initialize();

	int LoadVoice(const TCHAR* filePath);

	std::unordered_map<std::string, int> _vc;  // ���f�[�^
};
extern BossVoice gBossVoice;
