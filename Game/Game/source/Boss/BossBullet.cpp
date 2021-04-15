/**
 * @file   BossBullet.cpp
 * @brief  ボスの弾幕処理
 * 
 * @author matsuo tadahiko
 * @date   2020/12/22
 */

#include "BossBullet.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

BossBullet::BossBullet(VECTOR pos, float shotSpd, float shotAngle){

	_mh = resource::ResourceServer::MV1LoadModel("res/model/boss/bullet.mv1");
	_shadowModel = resource::ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = resource::ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = resource::ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;
	_shotSpd = shotSpd;
	_shotAngle = shotAngle;

	// 初期化
	ShotBase::Initialize();
}

BossBullet::~BossBullet(){
	// 何もしない
}

/*
 * 弾き返し処理
 */
void BossBullet::Repel() {

	_shotSpd = REPEL_SPD;     // 弾の移動速度変更(加速)
	_repelFlag = true;        // 弾き返されたのでフラグを立てる
	gGlobal._totalRepelCnt++; // 弾き返し回数カウント(スコア計算用)
}

/*
 * 当たり判定：プレイヤーの近接攻撃
 */
void BossBullet::CollisionToPlayerAttack() {

	// プレイヤーの位置情報取得
	VECTOR plPos = player::Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = util::Sqrt(sx, sz);  // プレイヤーとの距離計算

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	for (auto&& itr : *modeGame->_objServer.List()) {
		// プレイヤーの近接攻撃による弾き返し
		if (player::Player::GetInstance()->_canHitFlag && !itr->_hitFlag) {
			if (length < 4.0f) {
				_state = STATE::REPEL;
				Repel(); // 弾き返し処理
				itr->_hitFlag = true;
			}
		}
	}
}

/*
 * フレーム処理：計算
 */
void BossBullet::Process(){

	// 弾の移動処理
	ShotBase::Process();
	
	// 当たり判定
	CollisionToPlayerAttack();
}