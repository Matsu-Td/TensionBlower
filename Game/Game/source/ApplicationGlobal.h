
/**
 * @file  ApplicationGlobal.h
 * @brief グローバル変数定義
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class ApplicationGlobal{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	bool _gameEndFlag;    // ゲーム終了フラグ(true:ゲーム終了)
	int  _gameTime;       // クリアまでの経過時間
	int  _remainingHP;    // 残りHP
	int  _totalGetEnergy; // 総エネルギー回収量
	int  _totalRepelCnt;  // 合計弾き返し回数
};

extern ApplicationGlobal gGlobal; 