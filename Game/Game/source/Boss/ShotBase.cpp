/**
 * @file   ShotBase.cpp
 * @brief  弾幕系処理クラスの基底クラス
 * 
 * @author matsuo tadahiko
 * @date   2021/01/10
 */

#include "ShotBase.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

/*
 * 初期化
 */
void ShotBase::Initialize() {

	_state = STATE::NORMAL;
	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;

	_r = 1.5f;
}

/*
 * 弾の移動処理
 */
void ShotBase::Move() {

	// カメラの状態を取得
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();

	// ワールド座標 ⇒ スクリーン座標へ変換
	_scrnPos = ConvWorldPosToScreenPos(_vPos);

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	// マルチロックオンシステム発動時
	if (camState == camera::Camera::STATE::MLS_LOCK) {
		_mvSpd = _shotSpd * MLS_SPD; // マルチロックオンシステム中は速度0.01倍
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // 通常時の弾の速度
		_camStateMLS = false;
	}

	// 通常状態での移動
	if (_state == STATE::NORMAL) {
		float vx, vz;
		vx = cos(Util::DegToRad(_shotAngle)) * _mvSpd;
		vz = sin(Util::DegToRad(_shotAngle)) * _mvSpd;
		_vPos.x += vx;
		_vPos.z += vz;
	}

	// 弾き返された状態
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
}

/*
 * 各種当たり判定呼び出し
 */
void ShotBase::CollisionCall() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));

	for (auto&& itr : *modeGame->_objServer.List()) {
		CollisionToStage(itr);
		CollisionToBoss(itr);
		CollisionToPlayer(itr);
		CollisionToReticle(itr);
	}
}

/*
 * 当たり判定：ステージ
 */
void ShotBase::CollisionToStage(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
		if (IsHitStage(*obj, 0.8f) == true) {
			mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Del(this);

			MV1CollResultPolyDimTerminate(obj->_hitPolyDim);
		}
	}
}

/*
 * 当たり判定：ボス
 */
void ShotBase::CollisionToBoss(ObjectBase* obj) {

	if (_state == STATE::REPEL) {
		if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*obj, obj->_r) == true) {
				mode::ModeGame* modeGame = static_cast<mode::ModeGame*> (ModeServer::GetInstance()->Get("game"));
				modeGame->_objServer.Del(this);

				Boss::GetInstance()->RepelDamage();
			}
		}
	}
}

/*
 * 当たり判定：プレイヤー
 */
void ShotBase::CollisionToPlayer(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
		// マルチロックオンシステムによる弾き返し可能かどうか
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
void ShotBase::CollisionToReticle(ObjectBase* obj) {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (obj->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
		if (IsHitScrnPos(*obj) == true) {
			if (_canLockFlag) {
				if (trg & PAD_INPUT_2) {
					_state = STATE::REPEL;
					_shotSpd = REPEL_SPD;     // 弾の移動速度変更(加速)
					_repelFlag = true;        // 弾き返されたのでフラグを立てる
					gGlobal._totalRepelCnt++; // 弾き返し回数カウント(スコア計算用)
				}
			}
		}
	}
}

/*
 * フレーム処理：計算
 */
void ShotBase::Process(){

	Move();

	CollisionCall();
}

/*
 * フレーム処理：描画
 */
void ShotBase::Render(){

	float modelSize = 0.005f;
	ObjectBase::ShadowRender(modelSize);
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
	
	float graphSizeX = 40.0f;   // 画像サイズX
	float graphSizeY = 35.0f;   // 画像サイズY
	
	// マルチロックオンが可能か
	if (_canLockFlag) {
		// 弾き返されたかどうか
		if (_repelFlag) {
			DrawGraph(static_cast<int>(_scrnPos.x - graphSizeX), static_cast<int>(_scrnPos.y - graphSizeY), _cg[1], TRUE);
		}
		else {
			DrawGraph(static_cast<int>(_scrnPos.x - graphSizeX), static_cast<int>(_scrnPos.y - graphSizeY), _cg[0], TRUE);
		}
	}
}