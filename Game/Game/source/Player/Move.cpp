/** 
 * @file   Move.cpp
 * @brief  �v���C���[�̈ړ�����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

/*
 * �ړ�����
 */
void Player::Move() {

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);

	// ���A�i���O�X�e�B�b�N���W
	float lx, ly;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �J�����f�[�^�擾
	VECTOR camPos = Camera::GetInstance()->GetPos();      // �J�����ʒu
	VECTOR camTarg = Camera::GetInstance()->GetTarg();    // �J�����̒����_

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.0f,0.0f,0.0f };
	_analogLength = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);


	// �ړ�����
	if (_analogLength < ANALOG_MIN) {
		_analogLength = 0.0f;
	}
	else {
		_analogLength = _mvSpd;
	}

	// vec��rad����]������
	vec.x = cos(rad + camRad) * _analogLength;
	vec.z = sin(rad + camRad) * _analogLength;

	// vec�̕��ړ�
	_vPos = VAdd(_vPos, vec);

	// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	if (VSize(vec) > 0.0f) {		// �ړ����Ă��Ȃ����͖�������
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		LeftAnalogDeg();

		if (!_isDash) {
			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
		}

	}
	else if (_canJump && !_isAttack) {
		_state = STATE::WAIT;
	}
}


