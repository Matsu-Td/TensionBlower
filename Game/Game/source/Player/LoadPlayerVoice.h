/**
 * @file   LoadPlayerVoice.h
 * @brief  プレイヤー声優 声データ読み込み処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include <unordered_map>

namespace tensionblower {

	namespace player {

		/**
		 * @brief プレイヤー声優 声データ読み込み処理
		 */
		class LoadPlayerVoice {
		public:
			/**
			 * @brief 声データ読み込み
			 */
			void Initialize();

			/**
			 * @brief 声データ読み込み
			 * @param filePath ファイルパス指定
			 * @return 読み込んだデータのハンドル
			 */
			int LoadVoice(const TCHAR* filePath);

			std::unordered_map<std::string, int> _vc;  // 声データ
		};
	}
}
extern tensionblower::player::LoadPlayerVoice gPlayerVoice;