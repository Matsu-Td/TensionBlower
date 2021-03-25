/**
 * @file   ShotBase.cpp
 * @brief  �e�������N���X�̊��N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "ShotBase.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"

/**
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

/**
 * �e�̈ړ�����
 */
void ShotBase::Move() {

	// �J�����̏�Ԃ��擾
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// ���[���h���W �� �X�N���[�����W�֕ϊ�
	_scrnPos = ConvWorldPosToScreenPos(_vPos);

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	// �}���`���b�N�I���V�X�e��������
	if (camState == Camera::STATE::MLS_LOCK) {
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
		vx = cos(_shotAngle / 180.0f * DX_PI_F) * _mvSpd;
		vz = sin(_shotAngle / 180.0f * DX_PI_F) * _mvSpd;
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

void ShotBase::Process(){

}

/**
 * �t���[�������F�`��
 */
void ShotBase::Render(){

	float modelSize = 0.005f;
	ObjectBase::ShadowRender(modelSize);
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
	
	// �}���`���b�N�I�����\��
	if (_canLockFlag) {
		// �e���Ԃ��ꂽ���ǂ���
		if (_repelFlag) {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[1], TRUE);
		}
		else {
			DrawGraph(static_cast<int>(_scrnPos.x - 40.0f), static_cast<int>(_scrnPos.y - 35.0f), _cg[0], TRUE);
		}
	}
}

/**
 * �����蔻��
 */
void ShotBase::Collision(){

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// �X�e�[�W
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 0.8f) == true) {
				modeGame->_objServer.Del(this);
				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
			}
		}
		// �{�X�i�e���Ԃ��ꂽ�e�̂ݓ����蔻�蔭���j
		if (_state == STATE::REPEL) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
				if (IsHitLineSegment(*(*itr), (*itr)->_r) == true) {
					modeGame->_objServer.Del(this);
					_bossDamageCall->RepelDamage(Boss::GetInstance());
				}
			}
		}
		// �v���C���[
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
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
						_shotSpd = REPEL_SPD;     // �e�̈ړ����x�ύX(����)
						_repelFlag = true;        // �e���Ԃ��ꂽ�̂Ńt���O�𗧂Ă�
						gGlobal._totalRepelCnt++; // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
					}
				}
			}
		}
	}
}
