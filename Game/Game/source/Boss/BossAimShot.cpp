/**
 * @file   BossAimShot.cpp
 * @brief  ボスの狙い撃ち弾処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/21
 */

#include "BossAimShot.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

BossAimShot::BossAimShot(VECTOR pos, float shotSpd, float shotAngle){

	_mh = resource::ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");

	_shadowModel = resource::ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = resource::ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = resource::ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;
	_shotSpd = shotSpd;
	_shotAngle = shotAngle;

	// 初期化
	ShotBase::Initialize();
}

BossAimShot::~BossAimShot() {
	// 何もしない
}

/*
 * フレーム処理：計算 
 */
void BossAimShot::Process() {

	ShotBase::Process();
}