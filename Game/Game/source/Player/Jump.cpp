/**
 * @file   Jump.cpp
 * @brief  �v���C���[�W�����v����
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "Player.h"
#include "../Mode/ModeGame.h"

/*
 * �W�����v����
 */
void Player::Jump() {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �G�l���M�[�ʊm�F
	if (_energy >= modeGame->_charaData->_egJump) {
		if (trg & PAD_INPUT_1 && _canJump && !_isCharging) {
			_state = Player::STATE::JUMP;
			_canJump = false;
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
			_jumpTime = 0.0f;
		}
	}
	// �W�����v����
	if (!_canJump) {
		_vPos.y = IN_VEL * _jumpTime - MULT_HALF * GRAVITY * _jumpTime * _jumpTime;
	}

	_jumpTime += JUMP_CNT;

	// ���n
	if (_vPos.y < Player::GROUND_Y) {
		_vPos.y = Player::GROUND_Y;
		if (_isCharging == false) {
			_canJump = true;
		}
	}
}