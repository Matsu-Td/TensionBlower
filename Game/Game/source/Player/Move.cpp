/** 
 * @file   Move.cpp
 * @brief  �v���C���[�̈ړ�����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower;

/*
 * �ړ�����
 */
void Player::Move() {

	VECTOR camPos  = Camera::GetInstance()->GetPos();   // �J�����ʒu
	VECTOR camTarg = Camera::GetInstance()->GetTarg();  // �J�����̒����_
	float camRad   = Camera::GetInstance()->GetRad();   // �J�����̌����Ă���p�x�擾

	float length = Util::GetLeftStickLength(); 	// ���X�e�B�b�N�̈ړ���
	float rad    = Util::GetLeftStickRad();     // ���X�e�B�b�N�̊p�x(rad)

	VECTOR vec = { 0.0f,0.0f,0.0f };

	// �ړ�����
	if (length < Util::ANALOG_MIN) {
		length = 0.0f;
	}
	else {
		length = _mvSpd;
	}

	// vec��rad����]������
	vec.x = cos(rad + camRad) * length;
	vec.z = sin(rad + camRad) * length;

	// vec�̕��ړ�
	_vPos = VAdd(_vPos, vec);

	// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	if (VSize(vec) > 0.0f) {		// �ړ����Ă��Ȃ����͖�������
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		MoveAndDashMotionSwitch();

		if (!_isDash) {
			mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
		}
	}
	else if (_canJump && !_isAttack) {
		_state = STATE::WAIT;
	}
}


