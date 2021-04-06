/** 
 * @file   Charge.cpp
 * @brief  エネルギー溜め処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"

/*
 * エネルギー溜め処理
 */
void Player::Charge() {

	// キー入力情報取得
	int key = ApplicationMain::GetInstance()->GetKey();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5) && _energy < modeGame->_charaData->_maxEnergy) {
		if (_state != STATE::JUMP) {  // ジャンプしてなければ溜め可能
			if (!_isDash) {           // ダッシュしてなければ溜め可能
				_mvSpd = modeGame->_charaData->_mvSpdChrg;
				_isCharging = true;
			}
		}
	}
	else {
		_isCharging = false;
	}
}