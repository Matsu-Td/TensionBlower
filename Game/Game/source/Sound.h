/**
 * @file   Sound.h
 * @brief  BGM,SEì«Ç›çûÇ›
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

class Sound {
public:
	Sound();
	~Sound();

	/**
     * @brief BGM,SEì«Ç›çûÇ›
     */
	void Initialize();

	std::unordered_map<std::string, int> _bgm;  // BGM
	std::unordered_map<std::string, int> _se;   // SE
};
extern Sound gSound;  