/**
 * @file   BossBomb.cpp
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"
#include "../Effect/Explosion.h"
#include "../Sound/Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_shadowModel = ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {
	// 何もしない
}

/*
 * 上昇処理
 */
void BossBomb::StateUp() {

	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // カウントリセット
			_state = STATE::STOP;  // 停止状態に移行
		}
	}
}

/*
 * 停止処理
 */
void BossBomb::StateStop() {

	if (_state == STATE::STOP) {
		if (_shotCnt >= STOP_CNT) {
			_shotCnt = 0;
			// プレイヤー位置情報取得
			VECTOR plPos = Player::GetInstance()->GetPos();
			plPos.y = 0.0f;          // プレイヤーの足元(ステージ上)をターゲットとする
			_vTarg = plPos;          // プレイヤーをターゲットとする
			_state = STATE::SNIPER;  // 射撃状態に移行
		}
	}
}

/*
 * 狙撃処理
 */
void BossBomb::StateSniper() {

	if (_state == STATE::SNIPER) {
		// ターゲットに向かってボムを発射する
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, _mvSpd);
		_vPos = VAdd(_vPos, targ);
	}
}

/*
 * ボムの削除、爆発エフェクト生成
 */
void BossBomb::BombDelete() {

	if (_vPos.y <= 0.0f) {	
		Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);
	}
}

/*
 * 各種当たり判定呼び出し
 */
void BossBomb::CollisionCall() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	for (auto itr : *modeGame->_objServer.List()) {
		CollisionToPlayer(itr);
		CollisionToBoss(itr);
		CollisionToReticle(itr);
	}
}

/*
 * 当たり判定：プレイヤー
 */
void BossBomb::CollisionToPlayer(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
		if (IsHitLineSegment(*obj, _r)) {
			Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Add(explosion);
			modeGame->_objServer.Del(this);
		}
		if (IsDot(*obj) == true && _camStateMLS) {
			_canLockFlag = true;
		}
		else {
			_canLockFlag = false;
		}
	}
}

/*
 * 当たり判定：照準
 */
void BossBomb::CollisionToReticle(ObjectBase* obj) {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (obj->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
		if (IsHitScrnPos(*obj) == true) {
			if (_canLockFlag) {
				if (trg & PAD_INPUT_2) {
					_state = STATE::REPEL;
					gGlobal._totalRepelCnt++;    // 弾き返し回数カウント(スコア計算用)
				}
			}
		}
	}
}

/*
 * 当たり判定：ボス
 */
void BossBomb::CollisionToBoss(ObjectBase* obj) {

	if (_state == STATE::REPEL) {
		if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*obj, obj->_r)) {
				Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				modeGame->_objServer.Add(explosion);
				modeGame->_objServer.Del(this);
			}
		}
	}
}

/*
 * 初期化
 */
void BossBomb::Initialize() {

	ShotBase::Initialize();

	_mvSpd = 2.0f;
	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;
}

/*
 * フレーム処理：計算
 */
void BossBomb::Process() {

	ShotBase::Process();

	// 狙撃までのカウント
	_shotCnt++;

	// 上昇処理
	StateUp();

	// 停止処理
	StateStop();

	// 狙撃処理
	StateSniper();

	// ステージ床まで下降したらボムを削除
	BombDelete();
}
