/**
 * @file   PlayerVoice.h
 * @brief  プレイヤー声優 声データ読み込み
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

class PlayerVoice {
public:
	/**
	 * @brief 声データ読み込み
	 */
	void Init();

	int LoadVoice(const TCHAR* filePath);

	std::unordered_map<std::string, int> _vc;  // 声データ
};
extern PlayerVoice gPlayerVoice;