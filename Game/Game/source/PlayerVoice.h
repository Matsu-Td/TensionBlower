/**
 * @file   PlayerVoice.h
 * @brief  �v���C���[���D ���f�[�^�ǂݍ���
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
	 * @brief ���f�[�^�ǂݍ���
	 */
	void Init();

	int LoadVoice(const TCHAR* filePath);

	std::unordered_map<std::string, int> _vc;  // ���f�[�^
};
extern PlayerVoice gPlayerVoice;