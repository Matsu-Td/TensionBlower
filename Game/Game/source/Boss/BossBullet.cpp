/**
 * @file   BossBullet.cpp
 * @brief  �{�X�̒e������
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

	// ������
	ShotBase::Initialize();
}

BossBullet::~BossBullet(){
	// �������Ȃ�
}

/*
 * �e���Ԃ�����
 */
void BossBullet::Repel() {

	_shotSpd = REPEL_SPD;     // �e�̈ړ����x�ύX(����)
	_repelFlag = true;        // �e���Ԃ��ꂽ�̂Ńt���O�𗧂Ă�
	gGlobal._totalRepelCnt++; // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
}

/*
 * �����蔻��F�v���C���[�̋ߐڍU��
 */
void BossBullet::CollisionToPlayerAttack() {

	// �v���C���[�̈ʒu���擾
	VECTOR plPos = player::Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = util::Sqrt(sx, sz);  // �v���C���[�Ƃ̋����v�Z

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	for (auto&& itr : *modeGame->_objServer.List()) {
		// �v���C���[�̋ߐڍU���ɂ��e���Ԃ�
		if (player::Player::GetInstance()->_canHitFlag && !itr->_hitFlag) {
			if (length < 4.0f) {
				_state = STATE::REPEL;
				Repel(); // �e���Ԃ�����
				itr->_hitFlag = true;
			}
		}
	}
}

/*
 * �t���[�������F�v�Z
 */
void BossBullet::Process(){

	// �e�̈ړ�����
	ShotBase::Process();
	
	// �����蔻��
	CollisionToPlayerAttack();
}