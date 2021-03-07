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

	_cg[0] = ResourceServer::LoadGraph("res/仮素材/ロック可能.png");
	_cg[1] = ResourceServer::LoadGraph("res/仮素材/ロック確定.png");

	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {

}

void BossBomb::Initialize() {

	_mvSpd = 2.0f;
	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;

	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;

	_r = 1.5f;
}

void BossBomb::Process() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // カメラの状態を取得

	if (camState == Camera::STATE::MLS_LOCK) {
		_mvSpd = _shotSpd * 0.01f; // マルチロックオンシステム中は速度0.01倍
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // 通常時の弾の速度
		_camStateMLS = false;
	}

	// 狙撃までのカウント
	_shotCnt++;

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	_scrnPos = ConvWorldPosToScreenPos(_vPos);  // ワールド座標 ⇒ スクリーン座標へ変換

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

	// 弾き返し処理
	if (_state == STATE::REPEL) {
		_repelFlag = true;
		VECTOR bsPos = Boss::GetInstance()->GetPos();
		bsPos.y += 8.5f;
		_vTarg = bsPos;
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

	// プレイヤーとの当たり判定(当たった時点で爆発する)
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			// 着弾
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
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) { // レチクル
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_state = STATE::REPEL;
						gGlobal._totalRepelCnt++;    // 弾き返し回数カウント(スコア計算用)
					}
				}
			}
		}
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

void BossBomb::Render() {
	
	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
	MV1DrawModel(_mh);

	if (_canLockFlag) {
		//	DrawBox(_scrnPos.x + _hitX, _scrnPos.y + _hitY, _scrnPos.x + _hitW, _scrnPos.y + _hitH, GetColor(255, 0, 0), TRUE);
		if (_repelFlag) {
			DrawGraph(_scrnPos.x - 40.0f, _scrnPos.y - 35.0f, _cg[1], TRUE);
		}
		else {
			DrawGraph(_scrnPos.x - 40.0f, _scrnPos.y - 35.0f, _cg[0], TRUE);
		}
	}
//	DrawCapsule3D(_capsulePos1, _capsulePos2, _r, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
}
