/**
 * @file   Sound.h
 * @brief  BGM,SE�ǂݍ��ݏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/02/13
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

/**
 * @brief BGM,SE�ǂݍ��ݏ���
 */
class Sound {
public:
	/**
     * @brief BGM,SE�ǂݍ��ݏ���
     */
	void Initialize();

	std::unordered_map<std::string, int> _bgm;  // BGM
	std::unordered_map<std::string, int> _se;   // SE
};
extern Sound gSound;  