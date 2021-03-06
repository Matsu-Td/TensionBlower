/**
 * @file   Sound.h
 * @brief  BGM,SE読み込み処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/13
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

namespace tensionblower {

	namespace sound {
		/**
		 * @brief BGM,SE読み込み処理
		 */
		class Sound {
		public:
			/**
			 * @brief BGM,SE読み込み処理
			 */
			void Initialize();

			std::unordered_map<std::string, int> _bgm;  // BGM
			std::unordered_map<std::string, int> _se;   // SE
		};
	}
}
extern tensionblower::sound::Sound gSound;