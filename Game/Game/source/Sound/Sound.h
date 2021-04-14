/**
 * @file   Sound.h
 * @brief  BGM,SE“Ç‚İ‚İˆ—
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
		 * @brief BGM,SE“Ç‚İ‚İˆ—
		 */
		class Sound {
		public:
			/**
			 * @brief BGM,SE“Ç‚İ‚İˆ—
			 */
			void Initialize();

			std::unordered_map<std::string, int> _bgm;  // BGM
			std::unordered_map<std::string, int> _se;   // SE
		};
	}
}
extern tensionblower::sound::Sound gSound;