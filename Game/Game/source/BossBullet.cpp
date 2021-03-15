/**
 * @file   BossBullet.cpp
 * @brief  ボスの弾幕処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "BossBullet.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"

BossBullet::BossBullet(VECTOR pos, float shotSpd, float shotAngle){

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bullet.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;
	_shotSpd = shotSpd;
	_shotAngle = shotAngle;

	Initialize();
}

BossBullet::~BossBullet(){

}

/**
 * 初期化
 */
void BossBullet::Initialize(){

	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;
	_bulletDir = 1.0f;
	_r = 1.5f;
}

/**
 * 弾の移動処理
 */
void BossBullet::MoveShot(){
	
	// カメラの状態を取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState(); 

	if(camState == Camera::STATE::MLS_LOCK){
		_mvSpd = _shotSpd * MLS_SPD; // マルチロックオンシステム中は速度0.01倍
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // 通常時の弾の速度
		_camStateMLS = false;
	}
	
	float vx, vz;
	vx = cos(_shotAngle / 180.0f * DX_PI_F) * _mvSpd * _bulletDir;
	vz = sin(_shotAngle / 180.0f * DX_PI_F) * _mvSpd * _bulletDir;
	_vPos.x += vx;
	_vPos.z += vz;
}

/**
 * 弾き返し処理
 */
void BossBullet::Repel() {

	_bulletDir = -1.0f;       // 弾がはじき返される
	_shotSpd = REPEL_SPD;     // 弾の移動速度変更(加速)
	_repelFlag = true;        // 弾き返されたのでフラグを立てる
	gGlobal._totalRepelCnt++; // 弾き返し回数カウント(スコア計算用)
}

/**
 * 当たり判定
 */
void BossBullet::Collision() {

	// キーのトリガ入力取得
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// プレイヤーの位置情報取得
	VECTOR plPos = Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);  // プレイヤーとの距離計算

	// 当たり判定
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// ステージ
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 0.8f) == true) {
				modeGame->_objServer.Del(this);
				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
			}
		}
		// 照準
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						Repel(); // 弾き返し処理
					}
				}
			}
		}
		// ボス
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*(*itr), (*itr)->_r) == true) {
				if (_repelFlag) {
					modeGame->_objServer.Del(this);
					Boss::GetInstance()->RepelDamage();
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
		// プレイヤーの近接攻撃による弾き返し
		if (Player::GetInstance()->_canHitFlag && !(*itr)->_hitFlag) {
			if (length < 4.0f) {
				Repel(); // 弾き返し処理
				(*itr)->_hitFlag = true;
			}
		}
	}
}

/**
 * フレーム処理：計算
 */
void BossBullet::Process(){

	// 弾の移動処理
	MoveShot();

	// ワールド座標 ⇒ スクリーン座標へ変換
	_scrnPos = ConvWorldPosToScreenPos(_vPos);  
	
	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;
	
	// 当たり判定
	Collision();
}

/**
 * フレーム処理：描画
 */
void BossBullet::Render(){

	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
	
	if (_canLockFlag) {
		if (_repelFlag) {
			// ロック確定
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[1], TRUE);
		}
		else {
			// ロック可能
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[0], TRUE);
		}
	}
}