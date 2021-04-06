/** 
 * @file   Death.cpp
 * @brief  プレイヤーの死亡処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/26
 */

#include "Player.h"
#include "../Mode/ModeGameOver.h"

 /*
  * 死亡処理＆ゲームオーバーへ移行
  */
void Player::Death() {

	// ゲームオーバー
	if (_isGameOver) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = NEW ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	// ヒットポイント 0 でゲームオーバー
	if (_hitpoint <= 0) {
		_state = STATE::DEATH;
		_isGameOver = true;
	}

	// 死亡モーションは地上で行う
	if (_state == STATE::DEATH) {
		// 重力処理
		Gravity();
	}
}