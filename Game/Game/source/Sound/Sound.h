/**
 * @file   Sound.h
 * @brief  BGM,SE�ǂݍ��ݏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

/**
 * BGM,SE�ǂݍ��ݏ���
 */
class Sound {
public:
	/**
     * BGM,SE�ǂݍ��ݏ���
     */
	void Initialize();

	std::unordered_map<std::string, int> _bgm;  // BGM
	std::unordered_map<std::string, int> _se;   // SE
};
extern Sound gSound;  