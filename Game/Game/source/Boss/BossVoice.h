/**
 * @file   BossVoice.h
 * @brief  ボス声優 声データ読み込み
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
	 * 声データ読み込み
	 */
	void Initialize();

	int LoadVoice(const TCHAR* filePath);

	std::unordered_map<std::string, int> _vc;  // 声データ
};
extern BossVoice gBossVoice;
