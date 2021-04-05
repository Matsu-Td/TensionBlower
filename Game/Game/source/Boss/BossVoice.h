/**
 * @file   BossVoice.h
 * @brief  �{�X���D ���f�[�^�ǂݍ��ݏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/0$DAY
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

/**
 * @brief �{�X���D ���f�[�^�ǂݍ��ݏ���
 */
class BossVoice {
public:
	/**
	 * @brief ���f�[�^�ǂݍ���
	 */
	void Initialize();

	/**
	 * @brief ���f�[�^�ǂݍ���
	 * @param filePath �t�@�C���p�X�w��
	 * @return �ǂݍ��񂾃f�[�^�̃n���h��
	 */
	int LoadVoice(const TCHAR* filePath);

	std::unordered_map<std::string, int> _vc;  // ���f�[�^
};
extern BossVoice gBossVoice;
