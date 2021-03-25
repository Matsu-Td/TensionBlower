/**
 * @file   ShotBase.cpp
 * @brief  弾幕処理クラスの基底クラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "ShotBase.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"

/**
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

/**
 * 弾の移動処理
 */
void ShotBase::Move() {

	// カメラの状態を取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// ワールド座標 ⇒ スクリーン座標へ変換
	_scrnPos = ConvWorldPosToScreenPos(_vPos);

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	// マルチロックオンシステム発動時
	if (camState == Camera::STATE::MLS_LOCK) {
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
		vx = cos(_shotAngle / 180.0f * DX_PI_F) * _mvSpd;
		vz = sin(_shotAngle / 180.0f * DX_PI_F) * _mvSpd;
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

void ShotBase::Process(){

}

/**
 * フレーム処理：描画
 */
void ShotBase::Render(){

	float modelSize = 0.005f;
	ObjectBase::ShadowRender(modelSize);
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
	
	// マルチロックオンが可能か
	if (_canLockFlag) {
		// 弾き返されたかどうか
		if (_repelFlag) {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[1], TRUE);
		}
		else {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[0], TRUE);
		}
	}
}

/**
 * 当たり判定
 */
void ShotBase::Collision(){

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// ステージ
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 0.8f) == true) {
				modeGame->_objServer.Del(this);
				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
			}
		}
		// ボス（弾き返された弾のみ当たり判定発生）
		if (_state == STATE::REPEL) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
				if (IsHitLineSegment(*(*itr), (*itr)->_r) == true) {
					modeGame->_objServer.Del(this);
					_bossDamageCall->RepelDamage(Boss::GetInstance());
				}
			}
		}
		// プレイヤー
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
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
						_shotSpd = REPEL_SPD;     // 弾の移動速度変更(加速)
						_repelFlag = true;        // 弾き返されたのでフラグを立てる
						gGlobal._totalRepelCnt++; // 弾き返し回数カウント(スコア計算用)
					}
				}
			}
		}
	}
}
