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

using namespace tensionblower::player;

/*
 * �ړ�����
 */
void Player::Move() {

	VECTOR camPos  = camera::Camera::GetInstance()->GetPos();   // �J�����ʒu
	VECTOR camTarg = camera::Camera::GetInstance()->GetTarg();  // �J�����̒����_
	float camRad   = camera::Camera::GetInstance()->GetRad();   // �J�����̌����Ă���p�x�擾

	float length = util::GetLeftStickLength(); 	// ���X�e�B�b�N�̈ړ���
	float rad    = util::GetLeftStickRad();     // ���X�e�B�b�N�̊p�x(rad)

	VECTOR vec = { 0.0f,0.0f,0.0f };

	// �ړ�����
	if (length < util::ANALOG_MIN) {
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
			mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
		}
	}
	else if (_canJump && !_isAttack) {
		_state = STATE::WAIT;
	}
}


