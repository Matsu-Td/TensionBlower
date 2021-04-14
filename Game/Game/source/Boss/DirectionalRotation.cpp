/** 
 * @file   DirectionalRotation.cpp
 * @brief  �{�X���ʕ�����]����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Player/Player.h"

using namespace tensionblower::boss;

/*
 * �{�X���ʕ�����]����
 */
void Boss::DirectionalRotation(float rotSpdChange) {

	// �v���C���[�̈ʒu���擾
	VECTOR plPos = player::Player::GetInstance()->GetPos();

	// �{�X�̃t�H���[�h�x�N�g��
	VECTOR forward = { cos(_angle),0.0f,sin(_angle) };

	// �v���C���[�Ɍ������x�N�g��
	VECTOR dis = VSub(plPos, _vPos);
	// �P�ʃx�N�g����
	dis = VNorm(dis);

	// �O�ςŃv���C���[�̈ʒu�����E���肵�A�{�X�̌�������]������
	_cross = VCross(forward, dis);

	if (_cross.y > 0.0f) {
		_angle += ROT_SPD * rotSpdChange;
	}
	else if (_cross.y < 0.0f) {
		_angle -= ROT_SPD * rotSpdChange;
	}
	_vDir = { cos(_angle),0.0f,sin(_angle) };
}