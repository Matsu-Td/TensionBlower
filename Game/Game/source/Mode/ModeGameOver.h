/**
 * @file   ModeGameOver.h
 * @brief  ゲームオーバークラス
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief ゲームオーバークラス
		 */
		class ModeGameOver : public ::mode::ModeBase {
			using base = ModeBase;

		public:
			/**
			 * @brief  初期化
			 * @return 処理の成否
			 */
			bool Initialize() override;

			/**
			 * @brief  解放
			 * @return 処理の成否
			 */
			bool Terminate() override;

			/**
			 * @brief  フレーム処理：計算
			 * @return 処理の成否
			 */
			bool Process() override;

			/**
			 * @brief  フレーム処理：描画
			 * @return 処理の成否
			 */
			bool Render() override;

		private:
			int	_cg[2];	// 画像

			const int POS_Y = 390;  // 画像描画位置：Y座標
		};
	}
}
