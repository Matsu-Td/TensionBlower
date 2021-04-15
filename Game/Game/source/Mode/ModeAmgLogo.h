/**
 * @file   ModeAmgLogo.h
 * @brief  AMGロゴ描画処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {
		/**
		 * @brief AMGロゴ描画処理
		 */
		class ModeAmgLogo :public ::mode::ModeBase {
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
			int _bg;      // 背景
			int _cg;      // 画像
			int _mode;    // フェード制御モード
			int _fadeCnt; // フェードカウント 
			int _dispCnt; // 表示カウント
			int _alpha;   // 画像のα値

			const int MAX_ALPHA    = 255; // 画像α値の最大値
			const int MAX_FADE_CNT = 30;  // フェードカウント最大値
			const int MAX_DISP_CNT = 90;  // 描画カウント最大値
			const int LOGO_POS_X   = 460; // ロゴ画像X座標
			const int LOGO_POS_Y   = 425; // ロゴ画像Y座標
		};
	}
}
