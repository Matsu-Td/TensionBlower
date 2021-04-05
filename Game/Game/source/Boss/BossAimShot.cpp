/**
 * @file   BossAimShot.cpp
 * @brief  �{�X�̑_�������e����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "BossAimShot.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

BossAimShot::BossAimShot(VECTOR pos, float shotSpd, float shotAngle){

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_shadowModel = ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;
	_shotSpd = shotSpd;
	_shotAngle = shotAngle;

	// ������
	ShotBase::Initialize();
}

BossAimShot::~BossAimShot() {

}

/*
 * �t���[�������F�v�Z 
 */
void BossAimShot::Process() {

	// �L�[�̃g���K���͎擾
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �e�̈ړ�����
	ShotBase::Move();
		
	// �����蔻��
	ShotBase::Collision();
}