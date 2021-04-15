/**
 * @file   ModeResult.h
 * @brief  リザルトモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief リザルトモードクラス
		 */
		class ModeResult : public ::mode::ModeBase {
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
			int _cg;          // 画像
			int _timeScore;   // スコア：経過時間用
			int _hpScore;     // スコア：残りHP量用
			int _repelScore;  // スコア：総弾き回数
			int _energyScore; // スコア：総獲得エネルギー量用
			int _allScore;    // スコア：総スコア(全スコアの合計)

			const int MMSEC2SEC = 1000;          // ミリ秒⇒秒変換用
			const int MAX_SCORE = 100000;        // スコア最大値(経過時間、残りHP量用)
			const int TIME_LOWER = 120;           // 経過時間スコア減点スタート時間

			const int TIME_SCORE_PER_ONE = 200; // 経過時間のスコア基準計算値：1あたり
			const int HP_SCORE_PER_ONE = 100; // HPのスコア基準計算値：1あたり
			const int REPEL_SCORE_PER_ONE = 3000;// 弾き返し回数の基準計算値：1あたり
			const int ENERGY_SCORE_PER_ONE = 5;   // 総獲得エネルギーの基準計算値：1あたり
		};
	}
}
