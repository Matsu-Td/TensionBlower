/** 
 * @file   Down.cpp
 * @brief  ボスのダウン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

using namespace tensionblower::boss;

/*
 * ダウン処理
 */
void Boss::StateDown() {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();

	// 復帰
	if (_state == STATE::DOWN) {
		_vPos.y = 0.0f;
		_mlsDownFlag = false;	   // マルチロックオンシステムによるダウンフラグ解除
		_downTime--;               // ダウン時間カウント
		if (_downTime < 0) {
			// 復帰時の声データ再生
			PlayVoice("hukki");
			_downTime = 0;         // ダウン時間リセット
			_state = STATE::RETURN;// 復帰状態にさせる
			_bulletNum = 0;        // 弾の数リセット
			_shield = modeGame->_charaData->_boss.maxShield;  // シールド値全回復
		}
	}

	if (_shield > 0) {
		return;
	}
	// ダウン
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);

		for (auto&& itr : *modeGame->_objServer.List()) {
			if (itr->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // ダウン直前に出現していた弾の数をカウント
			}
			int plEnergy = player::Player::GetInstance()->GetEnergy();            // プレイヤーのエネルギー情報取得
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // ダウン時間計算                                           // ダウン状態にする
			_state = STATE::DOWN;
		}
	}
}