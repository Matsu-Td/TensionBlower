/**
 * @file   BossBomb.cpp
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"
#include "Explosion.h"
#include "Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/ui/lock_ok.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/lock_end.png");

	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {

}

/**
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

/**
 * �t���[�������F�v�Z
 */
void BossBomb::Process() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �e�̈ړ�����(�e�����ʏ���)
	ShotBase::Move();

	// �_���܂ł̃J�E���g
	_shotCnt++;

	// �㏸����
	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // �J�E���g���Z�b�g
			_state = STATE::STOP;  // ��~��ԂɈڍs
		}
	}

	// ��~����
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

	// �_������
	if (_state == STATE::SNIPER) {
		// �^�[�Q�b�g�Ɍ������ă{���𔭎˂���
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, _mvSpd);
		_vPos = VAdd(_vPos, targ);
	}

	// �X�e�[�W���܂ŉ��~������{�����폜
	if (_vPos.y <= 0.0f) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);
	}


	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// �v���C���[�Ƃ̓����蔻��(�����������_�Ŕ�������)
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHitLineSegment(*(*itr), _r)) {
				Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
				modeGame->_objServer.Add(explosion);
				modeGame->_objServer.Del(this);
			}
			if (IsDot(*(*itr)) == true && _camStateMLS) {
				_canLockFlag = true;
			}
			else {
				_canLockFlag = false;
			}	
		}
		// �Ə�
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_state = STATE::REPEL;
						gGlobal._totalRepelCnt++;    // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
					}
				}
			}
		}
		// �{�X�i�e���Ԃ��ꂽ�e�̂ݓ����蔻�蔭���j
		if (_state == STATE::REPEL) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
				if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
					Explosion* explosion = NEW Explosion(_vPos, _repelFlag);
					modeGame->_objServer.Add(explosion);
					modeGame->_objServer.Del(this);
				}
			}
		}
	}
}
