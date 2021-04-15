/**
 * @file   Explosion.cpp
 * @brief  ボム攻撃の爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#include "Explosion.h"
#include "../Mode/ModeGame.h"
#include "../Boss/Boss.h"
#include "../Player/Player.h"
#include "../Sound/Sound.h"
#include "../Camera/Camera.h"

using namespace tensionblower::effect;

Explosion::Explosion(VECTOR pos, bool repelFlag) {
	// 生成時、爆発音再生
	PlaySoundMem(gSound._se["explosion1"], DX_PLAYTYPE_BACK);

	_effectHandle  = resource::ResourceServer::LoadEffekseerEffect("res/effect/explosion/explosion.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_repelFlag = repelFlag;

	Initialize();
}

Explosion::~Explosion() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * 初期化
 */
void Explosion::Initialize() {

	_effectCnt = 0;
	_r = 0.0f;
}

/*
 * ボスとの当たり判定
 */
void Explosion::CollisionToBoss(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
		if (IsHitLineSegment(*obj, _r)) {
			// ヒットポイントへのダメージ：6フレーム毎にダメージ判定
			if (_effectCnt % 6 == 0) {
				boss::Boss::GetInstance()->ExplosionDamageHP();
			}
			// シールドへのダメージ：毎フレームダメージ判定
			boss::Boss::GetInstance()->ExplosionDamageShield();
		}
	}
}

/*
 * プレイヤーとの当たり判定
 */
void Explosion::CollisionToPlayer(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
		if (IsHitLineSegment(*obj, _r)) {
			player::Player::GetInstance()->ExplosionDamage();
		}
	}
}

/*
 * 各種当たり判定呼び出し
 */
void Explosion::CollisionCall() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	for (auto&& itr : *modeGame->_objServer.List()) {
		// プレイヤーに弾き返された弾かどうか
		if (_repelFlag) {
			// ボスにのみ当たり判定
			CollisionToBoss(itr);
		}
		else {
			// プレイヤーのみ当たり判定
			CollisionToPlayer(itr);
		}
	}
}

/*
 * フレーム処理：計算
 */
void Explosion::Process(){

	_effectCnt++;

	// 当たり判定用半径をエフェクトサイズに合わせて徐々に大きくする
	_r += 0.3f;
	if (_r >= MAX_RADIUS) {
		_r = MAX_RADIUS;
	}

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);

	// 総再生時間を迎えたらエフェクト削除
	if (_effectCnt >= ALL_EFFECT_TIME) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}

	// 各種当たり判定呼び出し
	CollisionCall();
}

/*
 * フレーム処理：描画
 */
void Explosion::Render(){
	// 何もしない
}
