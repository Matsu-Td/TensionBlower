/**
 * @file   Laser.cpp
 * @brief  �{�X�̃��[�U�[�U��
 * 
 * @author matsuo tadahiko
 * @date   2021/02/14
 */

#include "Laser.h"
#include "../Mode/ModeGame.h"
#include "../Boss/Boss.h"

Laser::Laser(VECTOR pos, float radius, float angle, float roteSpd) {

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/beam/effect_beam.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_roteAngle = angle;
	_roteSpd = roteSpd;
	_radius = radius;

	Initialize();
}

Laser::~Laser() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * ������
 */
void Laser::Initialize() {

	_r = 5.0f;
	_effectCnt = 240;
	_mlsCnt = 0;
}

/*
 * �폜����
 */
void Laser::Deletion() {

	// �{�X�̏�Ԃ��擾
	Boss::STATE bsState = Boss::GetInstance()->GetState();

	// �{�X���_�E�������烌�[�U�[�폜
	if (bsState == Boss::STATE::DOWN) {
		StopEffekseer3DEffect(_playingHandle);

		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}

	_effectCnt--;
	// �Đ��J�E���g���u0�v�ɂȂ�΃��[�U�[���폜����
	if (_effectCnt <= 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * �t���[�������F�v�Z
 */
void Laser::Process() {

	// �J�����̏�Ԃ��擾
	Camera::STATE camState = Camera::GetInstance()->GetState();

	// �}���`���b�N�I���V�X�e���������̉�]���x��1/100�ɂ���
	if (camState == Camera::STATE::MLS_LOCK) {
		_roteAngle += _roteSpd * MLS_SPD;
	}
	else {
		_roteAngle += _roteSpd;
	}

	// ���ˈʒu
	_vPos.x = cos(Util::DegToRad(_roteAngle)) * _radius;
	_vPos.z = sin(Util::DegToRad(_roteAngle)) * _radius;

	// ���[�U�[�̐�[(�X�e�[�W�O��)�̍��W
	VECTOR tmpPos;
	tmpPos.x = cos(Util::DegToRad(_roteAngle)) * LASER_LENGTH;
	tmpPos.y = 0.0f;
	tmpPos.z = sin(Util::DegToRad(_roteAngle)) * LASER_LENGTH;

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos2 = VAdd(_vPos, tmpPos);
	
	// ��������
	float angle = Util::DegToRad(-_roteAngle + 90.0f);

	// �ʒu�ƌ����v�Z
	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
	SetRotationPlayingEffekseer3DEffect(_playingHandle, 0.0f, angle, 0.0f);

	// �폜����
	Deletion();
}

/*
 * �t���[�������F�`��
 */
void Laser::Render() {
	// �������Ȃ�
}