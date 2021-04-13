/**
 * @file   Destruction.cpp
 * @brief  ボスの死亡爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "../Mode/ModeGame.h"
#include "../Mode/ModeGameClear.h"
#include "Destruction.h"

Destruction::Destruction(VECTOR pos){

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/destruction/effect_explosion_2.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_gameClearCnt = 200;
}

Destruction::~Destruction() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * フレーム処理：計算
 */
void Destruction::Process(){

	_gameClearCnt--;

	// ゲームクリアカウント「0」でエフェクト削除し、ゲームクリアに移行
	if (_gameClearCnt <= 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);

		ModeGameClear* modeGameClear = NEW ModeGameClear();
		ModeServer::GetInstance()->Add(modeGameClear, 2, "clear");
	}
	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
}

/*
 * フレーム処理：描画
 */
void Destruction::Render(){
	// 何もしない
}
