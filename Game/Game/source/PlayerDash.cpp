/**
 * @file   PlayerDash.cpp
 * @brief  �v���C���[�_�b�V������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerDash.h"

PlayerDash::PlayerDash() {

}

/**
 * �J�������b�N���̈ړ��A�_�b�V�����[�V����,�ړ��ˌ����[�V�����ؑ֏���
 * ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
 */
void PlayerDash::LeftAnalogDeg(Player* player, float length) {

	if (!player->_canJump) {
		return;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_isDash) {
		// �_�b�V���p�ړ����x�Z�b�g
		player->_mvSpd = modeGame->_charaData->_mvSpdDash;
		// �O�����_�b�V���ړ�
		if (player->_lfAnalogDeg >= ANALOG_REG_FOR || player->_lfAnalogDeg <= -ANALOG_REG_FOR) {
			player->_state = Player::STATE::FOR_DASH;
		}
		// �������_�b�V���ړ�
		else if (player->_lfAnalogDeg < -ANALOG_REG_OTHER && player->_lfAnalogDeg > -ANALOG_REG_FOR) {
			player->_state = Player::STATE::LEFT_DASH;
			
		}
		// �E�����_�b�V���ړ�
		else if (player->_lfAnalogDeg > ANALOG_REG_OTHER && player->_lfAnalogDeg < ANALOG_REG_FOR) {
			player->_state = Player::STATE::RIGHT_DASH;
			
		}
		// ������_�b�V���ړ�
		else if (player->_lfAnalogDeg >= -ANALOG_REG_OTHER && player->_lfAnalogDeg <= ANALOG_REG_OTHER && length >= ANALOG_MIN) {
			player->_state = Player::STATE::BACK_DASH;
		}
		// ���͂��Q�[���p�b�h�uRB�v�̂ݏꍇ�͑O�����_�b�V���ړ�
		else {
			player->_state = Player::STATE::FOR_DASH;
		}
	}
	else {
		// �ʏ�ړ����x�Z�b�g
		player->_mvSpd = modeGame->_charaData->_mvSpdNorm;
		// �O�����ړ�
		if (player->_lfAnalogDeg >= ANALOG_REG_FOR || player->_lfAnalogDeg <= -ANALOG_REG_FOR) {
			player->_state = Player::STATE::WALK;

		}
		// �������ړ�
		else if (player->_lfAnalogDeg < -ANALOG_REG_OTHER && player->_lfAnalogDeg > -ANALOG_REG_FOR) {
			player->_state = Player::STATE::LEFT_MOVE;
		}
		// �E�����ړ�
		else if (player->_lfAnalogDeg > ANALOG_REG_OTHER && player->_lfAnalogDeg < ANALOG_REG_FOR) {
			player->_state = Player::STATE::RIGHT_MOVE;
		}
		// ������ړ�
		else if (player->_lfAnalogDeg >= -ANALOG_REG_OTHER && player->_lfAnalogDeg <= ANALOG_REG_OTHER) {
			player->_state = Player::STATE::BACK_MOVE;
		}
	}
}

void PlayerDash::Dash(Player* player, float nowAngle, float length) {

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // �J�����̏��

	// �Z�����_�b�V��
	VECTOR vDash{ 0.0f,0.0f,00.f };      // �_�b�V���������
	if (trg & PAD_INPUT_6 && (player->_state != Player::STATE::JUMP) && player->_energy > modeGame->_charaData->_egDash) {
		player->_mvSpd = modeGame->_charaData->_mvSpdDash;  // �_�b�V���ړ����x�Z�b�g
		player->_isShortDash = true;              // �Z�����_�b�V���ړ��X�^�[�g
		player->_canLongDash = true;              // �Z�����_�b�V������ �� �������_�b�V�������\�ƂȂ�
		player->_shortDashTime = SHORT_DASH_CNT;  // �Z�����_�b�V���ړ����Ԃ��Z�b�g

	}
	if (player->_isShortDash) {
		player->_shortDashTime--;  
		if (player->_shortDashTime > 0) {
			player->_isDash = true;  // �_�b�V���X�^�[�g
			// �L�[���͂�����Ƃ����͕����Ƀ_�b�V������
			if (camState != Camera::STATE::TARG_LOCK_ON) {
				player->_state = Player::STATE::FOR_DASH;
			}
			player->_isCharging = false;   // �_�b�V�������ߍs���s��
			// �L�[���͂��Ȃ��Ƃ������Ă�������ɒ����Ń_�b�V������
			if (length < ANALOG_MIN) {
				if (camState == Camera::STATE::TARG_LOCK_ON) {
					LeftAnalogDeg(player, length);
					vDash.x = -cos(player->_bsAngle) * player->_mvSpd;
					vDash.z = -sin(player->_bsAngle) * player->_mvSpd;
				}
				else {
					vDash.x = cos(nowAngle) * player->_mvSpd;
					vDash.z = sin(nowAngle) * player->_mvSpd;
				}
				player->_vPos.x += vDash.x;
				player->_vPos.z += vDash.z;
			}
		}
		else {
			player->_shortDashTime = 0;
			player->_isShortDash = false;
			player->_isDash = false;
		}
	}
	// �������_�b�V��
	if (key & PAD_INPUT_6) {
		//�v���C���[���n��ɂ��� �A�������_�b�V���\(�Z�����_�b�V�����s������)�A�Z�����_�b�V���ړ����I����Ă���A�G�l���M�[0��肠��
		if (player->_canJump && player->_canLongDash && !player->_isShortDash && player->_energy > 0) {
			player->_isDash = true;       // �_�b�V����Ԃɂ���
			player->_isCharging = false;  // �_�b�V�������ߍs���s��
			// �L�[���͂�����Ƃ������͕����Ƀ_�b�V������
			if (camState != Camera::STATE::TARG_LOCK_ON) {
				player->_state = Player::STATE::FOR_DASH;
			}
			// �L�[���͂��Ȃ��Ƃ��F�����Ă�������ɒ����Ń_�b�V������
			if (length < ANALOG_MIN) {
				if (camState == Camera::STATE::TARG_LOCK_ON) {
					LeftAnalogDeg(player, length);
					vDash.x = -cos(player->_bsAngle) * player->_mvSpd;
					vDash.z = -sin(player->_bsAngle) * player->_mvSpd;
					player->_vPos.x += vDash.x;
					player->_vPos.z += vDash.z;
				}
				else {
					vDash.x = cos(nowAngle) * player->_mvSpd;
					vDash.z = sin(nowAngle) * player->_mvSpd;
					player->_vPos.x += vDash.x;
					player->_vPos.z += vDash.z;
				}
			}
		}
	}
	else {
		player->_isDash = false;
		player->_canLongDash = false;
	}
}