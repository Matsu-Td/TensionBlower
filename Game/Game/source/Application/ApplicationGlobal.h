/**
 * @file   ApplicationGlobal.h
 * @brief  グローバル変数定義
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#include "appframe.h"

namespace tensionblower {

	/**
	 * @brief グローバル変数定義
	 */
	class ApplicationGlobal {
	public:
		ApplicationGlobal();
		virtual ~ApplicationGlobal();

		/**
		 * @brief  初期化
		 * @return 処理の成否
		 */
		bool Initialize();

	public:
		bool _gameEndFlag;    // ゲーム終了フラグ(true:ゲーム終了)
		int  _gameTime;       // クリアまでの経過時間
		int  _remainingHP;    // 残りHP
		int  _totalGetEnergy; // 総エネルギー回収量
		int  _totalRepelCnt;  // 合計弾き返し回数
	};
}
extern tensionblower::ApplicationGlobal gGlobal;