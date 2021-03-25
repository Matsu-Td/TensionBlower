/**
 * @file   BossAimShot.cpp
 * @brief  ボスの狙い撃ち弾
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "BossAimShot.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"

BossAimShot::BossAimShot(VECTOR pos, float shotSpd, float shotAngle){

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_shadowModel = ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;
	_shotSpd = shotSpd;
	_shotAngle = shotAngle;

	// 初期化
	ShotBase::Initialize();
}

BossAimShot::~BossAimShot() {

}


void BossAimShot::Process() {

	// キーのトリガ入力取得
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// 弾の移動処理
	ShotBase::Move();
		
	// 当たり判定
	ShotBase::Collision();
}