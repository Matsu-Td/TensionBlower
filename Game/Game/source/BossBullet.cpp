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

	// 初期化
	BulletBase::Initialize();
}

BossBullet::~BossBullet(){

}

/**
 * 弾き返し処理
 */
void BossBullet::Repel() {

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
	BulletBase::Collision();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// プレイヤーの近接攻撃による弾き返し
		if (Player::GetInstance()->_canHitFlag && !(*itr)->_hitFlag) {
			if (length < 4.0f) {
				_state = STATE::REPEL;
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
	BulletBase::Move();
	
	// 当たり判定
	Collision();
}