/**
 * @file   Dash.cpp
 * @brief  �v���C���[�_�b�V������
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"

/*
 * �ړ��A�_�b�V�����[�V�����ؑ֏���
 */
void Player::LeftAnalogDeg() {

	if (!_canJump) {
		return;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_isDash) {
		// �_�b�V���p�ړ����x�Z�b�g
		_mvSpd = modeGame->_charaData->_mvSpdDash;
		// �O�����_�b�V���ړ�
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = Player::STATE::FOR_DASH;
		}
		// �������_�b�V���ړ�
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = Player::STATE::LEFT_DASH;

		}
		// �E�����_�b�V���ړ�
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = Player::STATE::RIGHT_DASH;

		}
		// ������_�b�V���ړ�
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER && _analogLength >= ANALOG_MIN) {
			_state = Player::STATE::BACK_DASH;
		}
		// ���͂��Q�[���p�b�h�uRB�v�̂ݏꍇ�͑O�����_�b�V���ړ�
		else {
			_state = Player::STATE::FOR_DASH;
		}
	}
	else {
		// �ʏ�ړ����x�Z�b�g
		_mvSpd = modeGame->_charaData->_mvSpdNorm;
		// �O�����ړ�
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = Player::STATE::WALK;
		}
		// �������ړ�
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = Player::STATE::LEFT_MOVE;
		}
		// �E�����ړ�
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = Player::STATE::RIGHT_MOVE;
		}
		// ������ړ�
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER) {
			_state = Player::STATE::BACK_MOVE;
		}
	}
}

/*
 * �_�b�V������
 */
void Player::Dash() {
	
	int key = ApplicationMain::GetInstance()->GetKey();// �L�[���͏��擾
	int trg = ApplicationMain::GetInstance()->GetTrg();// �L�[�̃g���K���擾

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // �J�����̏��

	// ���݂̃v���C���[�̐��ʊp�x
	float nowAngle = atan2(_vDir.z, _vDir.x);

	// �Z�����_�b�V��
	VECTOR vDash{ 0.0f,0.0f,00.f };      // �_�b�V���������
	if (trg & PAD_INPUT_6 && (_state != Player::STATE::JUMP) && _energy > modeGame->_charaData->_egDash) {
		_mvSpd = modeGame->_charaData->_mvSpdDash;  // �_�b�V���ړ����x�Z�b�g
		_isShortDash = true;              // �Z�����_�b�V���ړ��X�^�[�g
		_canLongDash = true;              // �Z�����_�b�V������ �� �������_�b�V�������\�ƂȂ�
		_shortDashTime = SHORT_DASH_CNT;  // �Z�����_�b�V���ړ����Ԃ��Z�b�g

	}
	if (_isShortDash) {
		_shortDashTime--;
		if (_shortDashTime > 0) {
			_isDash = true;  // �_�b�V���X�^�[�g
			// �L�[���͂�����Ƃ����͕����Ƀ_�b�V������
			if (camState != Camera::STATE::NORMAL) {
				_state = Player::STATE::FOR_DASH;
			}
			_isCharging = false;   // �_�b�V�������ߍs���s��
			// �L�[���͂��Ȃ��Ƃ������Ă�������ɒ����Ń_�b�V������
			if (_analogLength < ANALOG_MIN) {
				if (camState == Camera::STATE::NORMAL) {
					LeftAnalogDeg();
					vDash.x = -cos(_bsAngle) * _mvSpd;
					vDash.z = -sin(_bsAngle) * _mvSpd;
				}
				else {
					vDash.x = cos(nowAngle) * _mvSpd;
					vDash.z = sin(nowAngle) * _mvSpd;
				}
				_vPos.x += vDash.x;
				_vPos.z += vDash.z;
			}
		}
		else {
			_shortDashTime = 0;
			_isShortDash = false;
			_isDash = false;
		}
	}
	// �������_�b�V��
	if (key & PAD_INPUT_6) {
		//�v���C���[���n��ɂ��� �A�������_�b�V���\(�Z�����_�b�V�����s������)�A�Z�����_�b�V���ړ����I����Ă���A�G�l���M�[0��肠��
		if (_canJump && _canLongDash && !_isShortDash && _energy > 0) {
			_isDash = true;       // �_�b�V����Ԃɂ���
			_isCharging = false;  // �_�b�V�������ߍs���s��
			// �L�[���͂�����Ƃ������͕����Ƀ_�b�V������
			if (camState != Camera::STATE::NORMAL) {
				_state = Player::STATE::FOR_DASH;
			}
			// �L�[���͂��Ȃ��Ƃ��F�����Ă�������ɒ����Ń_�b�V������
			if (_analogLength < ANALOG_MIN) {
				if (camState == Camera::STATE::NORMAL) {
					LeftAnalogDeg();
					vDash.x = -cos(_bsAngle) * _mvSpd;
					vDash.z = -sin(_bsAngle) * _mvSpd;
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
				else {
					vDash.x = cos(nowAngle) * _mvSpd;
					vDash.z = sin(nowAngle) * _mvSpd;
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
			}
		}
	}
	else {
		_isDash = false;
		_canLongDash = false;
	}
}