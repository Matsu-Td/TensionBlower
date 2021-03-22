/**
 * @file   BossBullet.cpp
 * @brief  �{�X�̒e������
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

	// ������
	BulletBase::Initialize();
}

BossBullet::~BossBullet(){

}

/**
 * �e���Ԃ�����
 */
void BossBullet::Repel() {

	_shotSpd = REPEL_SPD;     // �e�̈ړ����x�ύX(����)
	_repelFlag = true;        // �e���Ԃ��ꂽ�̂Ńt���O�𗧂Ă�
	gGlobal._totalRepelCnt++; // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
}

/**
 * �����蔻��
 */
void BossBullet::Collision() {

	// �L�[�̃g���K���͎擾
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �v���C���[�̈ʒu���擾
	VECTOR plPos = Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);  // �v���C���[�Ƃ̋����v�Z

	// �����蔻��
	BulletBase::Collision();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// �v���C���[�̋ߐڍU���ɂ��e���Ԃ�
		if (Player::GetInstance()->_canHitFlag && !(*itr)->_hitFlag) {
			if (length < 4.0f) {
				_state = STATE::REPEL;
				Repel(); // �e���Ԃ�����
				(*itr)->_hitFlag = true;
			}
		}
	}
}

/**
 * �t���[�������F�v�Z
 */
void BossBullet::Process(){

	// �e�̈ړ�����
	BulletBase::Move();
	
	// �����蔻��
	Collision();
}