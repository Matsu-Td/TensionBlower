#pragma once

/**
 * @file Sound.h
 * @brief BGM,SE�ǂݍ���
 * 
 * @date 2021-02-13
 */

#include "appframe.h"
#include <unordered_map>

class Sound {
public:
	Sound();
	~Sound();

	/**
     * BGM,SE�ǂݍ���
     */
	void Init();

	std::unordered_map<std::string, int> _bgm;  // BGM
	std::unordered_map<std::string, int> _se;   // SE
};
extern Sound gSound;  