/**
 * @file   BossBomb.cpp
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"
#include "../Effect/Explosion.h"
#include "../Sound/Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_shadowModel = ResourceServer::MV1LoadModel("res/model/boss/bullet_shadow.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {
	// �������Ȃ�
}

/*
 * �㏸����
 */
void BossBomb::StateUp() {

	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // �J�E���g���Z�b�g
			_state = STATE::STOP;  // ��~��ԂɈڍs
		}
	}
}

/*
 * ��~����
 */
void BossBomb::StateStop() {

	if (_state == STATE::STOP) {
		if (_shotCnt >= STOP_CNT) {
			_shotCnt = 0;
			// �v���C���[�ʒu���擾
			VECTOR plPos = Player::GetInstance()->GetPos();
			plPos.y = 0.0f;          // �v���C���[�̑���(�X�e�[�W��)���^�[�Q�b�g�Ƃ���
			_vTarg = plPos;          // �v���C���[���^�[�Q�b�g�Ƃ���
			_state = STATE::SNIPER;  // �ˌ���ԂɈڍs
		}
	}
}

/*
 * �_������
 */
void BossBomb::StateSniper() {

	if (_state == STATE::SNIPER) {
		// �^�[�Q�b�g�Ɍ������ă{���𔭎˂���
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, _mvSpd);
		_vPos = VAdd(_vPos, targ);
	}
}

/*
 * �{���̍폜�A�����G�t�F�N�g����
 */
void BossBomb::BombDelete() {

	if (_vPos.y <= 0.0f) {	
		Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);
	}
}

/*
 * �e�퓖���蔻��Ăяo��
 */
void BossBomb::CollisionCall() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	for (auto itr : *modeGame->_objServer.List()) {
		CollisionToPlayer(itr);
		CollisionToBoss(itr);
		CollisionToReticle(itr);
	}
}

/*
 * �����蔻��F�v���C���[
 */
void BossBomb::CollisionToPlayer(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
		if (IsHitLineSegment(*obj, _r)) {
			Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Add(explosion);
			modeGame->_objServer.Del(this);
		}
		if (IsDot(*obj) == true && _camStateMLS) {
			_canLockFlag = true;
		}
		else {
			_canLockFlag = false;
		}
	}
}

/*
 * �����蔻��F�Ə�
 */
void BossBomb::CollisionToReticle(ObjectBase* obj) {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (obj->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
		if (IsHitScrnPos(*obj) == true) {
			if (_canLockFlag) {
				if (trg & PAD_INPUT_2) {
					_state = STATE::REPEL;
					gGlobal._totalRepelCnt++;    // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
				}
			}
		}
	}
}

/*
 * �����蔻��F�{�X
 */
void BossBomb::CollisionToBoss(ObjectBase* obj) {

	if (_state == STATE::REPEL) {
		if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*obj, obj->_r)) {
				Explosion* explosion = NEW Explosion(_vPos, _repelFlag);

				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				modeGame->_objServer.Add(explosion);
				modeGame->_objServer.Del(this);
			}
		}
	}
}

/*
 * ������
 */
void BossBomb::Initialize() {

	ShotBase::Initialize();

	_mvSpd = 2.0f;
	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;
}

/*
 * �t���[�������F�v�Z
 */
void BossBomb::Process() {

	ShotBase::Process();

	// �_���܂ł̃J�E���g
	_shotCnt++;

	// �㏸����
	StateUp();

	// ��~����
	StateStop();

	// �_������
	StateSniper();

	// �X�e�[�W���܂ŉ��~������{�����폜
	BombDelete();
}
