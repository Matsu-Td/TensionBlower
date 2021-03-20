/**
 * @file   BossHit.cpp
 * @brief  ボスへのヒットエフェクト
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "ModeGame.h"
#include "BossHit.h"

BossHit::BossHit(VECTOR pos) {

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/hit/hit.efkefc", 1.5f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;

	Initialize();
}

BossHit::~BossHit() {
	StopEffekseer3DEffect(_playingHandle);
}

/**
 * 初期化
 */
void BossHit::Initialize() {

	_effectCnt = 0;
}

/**
 * フレーム処理：計算
 */
void BossHit::Process() {

	_effectCnt++;

	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);

	// 総再生時間を迎えたらエフェクト削除
	if (_effectCnt >= ALL_EFFECT_TIME) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/**
 * フレーム処理：描画
 */
void BossHit::Render() {

}