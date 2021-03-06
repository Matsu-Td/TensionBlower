/** 
 * @file   BossDeath.cpp
 * @brief  ボスの死亡処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Effect/Destruction.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

 /*
  * 死亡処理
  */
void Boss::Death() {

	// ボスを削除
	if (_state == STATE::DEATH) {
		_deathCnt--;
		if (_deathCnt == 0) {
			MV1DeleteModel(_mh); // ボスモデルを削除する
		}
	}
	// ヒットポイントゼロでゲームクリアフラグを立てる
	if (_hitpoint <= 0) {
		if(_state != STATE::DEATH){
			// 撃破時の声データ再生
			PlayVoice("gekiha");
			VECTOR tmpPos = _vPos;
			tmpPos.y = 8.5f;

			effect::Destruction* destruction = NEW effect::Destruction(tmpPos);

			mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
			modeGame->_objServer.Add(destruction);
		}
		_hitpoint = 0;
		_state = STATE::DEATH;
	}
}