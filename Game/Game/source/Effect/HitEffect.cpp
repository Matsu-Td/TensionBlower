/**
 * @file   HitEffect.cpp
 * @brief  近接攻撃のヒットエフェクト
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "HitEffect.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::effect;

HitEffect::HitEffect(VECTOR pos) {

	_effectHandle  = resource::ResourceServer::LoadEffekseerEffect("res/effect/hit/hit.efkefc", 1.5f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;

	Initialize();
}

HitEffect::~HitEffect() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * 初期化
 */
void HitEffect::Initialize() {

	_effectCnt = 0;
}

/*
 * フレーム処理：計算
 */
void HitEffect::Process() {

	_effectCnt++;

	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);

	// 総再生時間を迎えたらエフェクト削除
	if (_effectCnt >= ALL_EFFECT_TIME) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * フレーム処理：描画
 */
void HitEffect::Render() {
	// 何もしない
}