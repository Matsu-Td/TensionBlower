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

BossBullet::BossBullet(){

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bullet.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");
	Initialize();
}

BossBullet::~BossBullet(){

}

/**
 * 初期化
 */
void BossBullet::Initialize(){

	_setAngle = 45.0f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_pattern = 0;
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
void BossBullet::Shot(){
	
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // カメラの状態を取得

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
 * フレーム処理：計算
 */
void BossBullet::Process(){

	int trg = ApplicationMain::GetInstance()->GetTrg();

	VECTOR plPos = Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);
	Shot(); // 弾発生処理

	_scrnPos = ConvWorldPosToScreenPos(_vPos);  // ワールド座標 ⇒ スクリーン座標へ変換
	
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;
	

	/**
	* 当たり判定
	*/
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {   // ステージ
			if (IsHitStage(*(*itr), 0.8f) == true) {
				modeGame->_objServer.Del(this);
				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) { // レチクル
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_bulletDir = -1.0f;   // 弾がはじき返される
						_repelFlag = true;    // 弾き返されたのでフラグを立てる
						gGlobal._totalRepelCnt++;    // 弾き返し回数カウント(スコア計算用)
					}
				}
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) { // ボス
			if (IsHitLineSegment(*(*itr), (*itr)->_r) == true) {
				if (_repelFlag) {
					modeGame->_objServer.Del(this);
					Boss::GetInstance()->Damage();
				}
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {  // プレイヤー
			if (IsDot(*(*itr)) == true && _camStateMLS) {
				_canLockFlag = true;
			}
			else {
				_canLockFlag = false;
			}
		}
	}
}

/**
 * フレーム処理：描画
 */
void BossBullet::Render(){

	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
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

#if 0
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _scrnPos.x, _scrnPos.y, _scrnPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  出現した弾の数(size())  = %d", _lsBlt.size());
	
#endif
}