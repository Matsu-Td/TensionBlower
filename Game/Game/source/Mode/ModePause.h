/**
 * @file   ModePause.h
 * @brief  ポーズモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/27
 */

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief ポーズモードクラス
		 */
		class ModePause : public ModeBase {
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
			int _cg;      // 画像
			int _ui[4];   // UI画像
			int _menuPos; // 選択位置

			const int POS_X = 786; // 画像描画位置：X座標(共通)
			const int POS_Y_UP = 380; // 画像描画位置：Y座標(上側)
			const int POS_Y_UNDER = 580; // 画像描画位置：Y座標(下側)
		};
	}
}
