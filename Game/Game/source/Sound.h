#pragma once

/**
 * @file Sound.h
 * @brief BGM,SEì«Ç›çûÇ›
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
     * BGM,SEì«Ç›çûÇ›
     */
	void Init();

	std::unordered_map<std::string, int> _bgm;  // BGM
	std::unordered_map<std::string, int> _se;   // SE
};
extern Sound gSound;  