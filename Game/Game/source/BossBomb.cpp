/**
 * @file   BossBomb.cpp
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"
#include "Explosion.h"
#include "Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {

}

/**
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

/**
 * フレーム処理：計算
 */
void BossBomb::Process() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// 弾の移動処理(弾幕共通処理)
	ShotBase::Move();

	// 狙撃までのカウント
	_shotCnt++;

	// 上昇処理
	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // カウントリセット
			_state = STATE::STOP;  // 停止状態に移行
		}
	}

	// 停止処理
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

	// 狙撃処理
	if (_state == STATE::SNIPER) {
		// ターゲットに向かってボムを発射する
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, _mvSpd);
		_vPos = VAdd(_vPos, targ);
	}

	// ステージ床まで下降したらボムを削除
	if (_vPos.y <= 0.0f) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);
	}


	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// プレイヤーとの当たり判定(当たった時点で爆発する)
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHitLineSegment(*(*itr), _r)) {
				Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
				modeGame->_objServer.Add(explosion);
				modeGame->_objServer.Del(this);
			}
			if (IsDot(*(*itr)) == true && _camStateMLS) {
				_canLockFlag = true;
			}
			else {
				_canLockFlag = false;
			}	
		}
		// 照準
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_state = STATE::REPEL;
						gGlobal._totalRepelCnt++;    // 弾き返し回数カウント(スコア計算用)
					}
				}
			}
		}
		// ボス（弾き返された弾のみ当たり判定発生）
		if (_state == STATE::REPEL) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
				if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
					Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
					modeGame->_objServer.Add(explosion);
					modeGame->_objServer.Del(this);
				}
			}
		}
	}
}
