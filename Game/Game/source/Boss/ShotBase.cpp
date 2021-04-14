/**
 * @file   ShotBase.cpp
 * @brief  �e���n�����N���X�̊��N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/01/10
 */

#include "ShotBase.h"
#include "Boss.h"
#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

/*
 * ������
 */
void ShotBase::Initialize() {

	_state = STATE::NORMAL;
	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;

	_r = 1.5f;
}

/*
 * �e�̈ړ�����
 */
void ShotBase::Move() {

	// �J�����̏�Ԃ��擾
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();

	// ���[���h���W �� �X�N���[�����W�֕ϊ�
	_scrnPos = ConvWorldPosToScreenPos(_vPos);

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	// �}���`���b�N�I���V�X�e��������
	if (camState == camera::Camera::STATE::MLS_LOCK) {
		_mvSpd = _shotSpd * MLS_SPD; // �}���`���b�N�I���V�X�e�����͑��x0.01�{
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // �ʏ펞�̒e�̑��x
		_camStateMLS = false;
	}

	// �ʏ��Ԃł̈ړ�
	if (_state == STATE::NORMAL) {
		float vx, vz;
		vx = cos(Util::DegToRad(_shotAngle)) * _mvSpd;
		vz = sin(Util::DegToRad(_shotAngle)) * _mvSpd;
		_vPos.x += vx;
		_vPos.z += vz;
	}

	// �e���Ԃ��ꂽ���
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
}

/*
 * �e�퓖���蔻��Ăяo��
 */
void ShotBase::CollisionCall() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));

	for (auto&& itr : *modeGame->_objServer.List()) {
		CollisionToStage(itr);
		CollisionToBoss(itr);
		CollisionToPlayer(itr);
		CollisionToReticle(itr);
	}
}

/*
 * �����蔻��F�X�e�[�W
 */
void ShotBase::CollisionToStage(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
		if (IsHitStage(*obj, 0.8f) == true) {
			mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Del(this);

			MV1CollResultPolyDimTerminate(obj->_hitPolyDim);
		}
	}
}

/*
 * �����蔻��F�{�X
 */
void ShotBase::CollisionToBoss(ObjectBase* obj) {

	if (_state == STATE::REPEL) {
		if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*obj, obj->_r) == true) {
				mode::ModeGame* modeGame = static_cast<mode::ModeGame*> (ModeServer::GetInstance()->Get("game"));
				modeGame->_objServer.Del(this);

				Boss::GetInstance()->RepelDamage();
			}
		}
	}
}

/*
 * �����蔻��F�v���C���[
 */
void ShotBase::CollisionToPlayer(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
		// �}���`���b�N�I���V�X�e���ɂ��e���Ԃ��\���ǂ���
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
void ShotBase::CollisionToReticle(ObjectBase* obj) {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (obj->GetType() == ObjectBase::OBJECTTYPE::RETICLE) {
		if (IsHitScrnPos(*obj) == true) {
			if (_canLockFlag) {
				if (trg & PAD_INPUT_2) {
					_state = STATE::REPEL;
					_shotSpd = REPEL_SPD;     // �e�̈ړ����x�ύX(����)
					_repelFlag = true;        // �e���Ԃ��ꂽ�̂Ńt���O�𗧂Ă�
					gGlobal._totalRepelCnt++; // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
				}
			}
		}
	}
}

/*
 * �t���[�������F�v�Z
 */
void ShotBase::Process(){

	Move();

	CollisionCall();
}

/*
 * �t���[�������F�`��
 */
void ShotBase::Render(){

	float modelSize = 0.005f;
	ObjectBase::ShadowRender(modelSize);
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
	
	float graphSizeX = 40.0f;   // �摜�T�C�YX
	float graphSizeY = 35.0f;   // �摜�T�C�YY
	
	// �}���`���b�N�I�����\��
	if (_canLockFlag) {
		// �e���Ԃ��ꂽ���ǂ���
		if (_repelFlag) {
			DrawGraph(static_cast<int>(_scrnPos.x - graphSizeX), static_cast<int>(_scrnPos.y - graphSizeY), _cg[1], TRUE);
		}
		else {
			DrawGraph(static_cast<int>(_scrnPos.x - graphSizeX), static_cast<int>(_scrnPos.y - graphSizeY), _cg[0], TRUE);
		}
	}
}