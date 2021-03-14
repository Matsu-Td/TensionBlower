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

	_mvSpd = 2.0f;
	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;

	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;

	_r = 1.5f;
}

/**
 * �t���[�������F�v�Z
 */
void BossBomb::Process() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // �J�����̏�Ԃ��擾

	if (camState == Camera::STATE::MLS_LOCK) {
		_mvSpd = _shotSpd * MLS_SPD; // �}���`���b�N�I���V�X�e�����͑��x0.01�{
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // �ʏ펞�̒e�̑��x
		_camStateMLS = false;
	}

	// �_���܂ł̃J�E���g
	_shotCnt++;

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	_scrnPos = ConvWorldPosToScreenPos(_vPos);  // ���[���h���W �� �X�N���[�����W�֕ϊ�

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

	// �e���Ԃ�����
	if (_state == STATE::REPEL) {
		_repelFlag = true;
		VECTOR bsPos = Boss::GetInstance()->GetPos();
		bsPos.y += 8.5f;
		_vTarg = bsPos;
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

	// �v���C���[�Ƃ̓����蔻��(�����������_�Ŕ�������)
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			// ���e
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
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) { // �Ə�
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_state = STATE::REPEL;
						gGlobal._totalRepelCnt++;    // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
					}
				}
			}
		}
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

/**
 * �t���[���v�Z�F�`��
 */
void BossBomb::Render() {
	
	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);

	if (_canLockFlag) {
		if (_repelFlag) {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[1], TRUE);
		}
		else {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[0], TRUE);
		}
	}
}
