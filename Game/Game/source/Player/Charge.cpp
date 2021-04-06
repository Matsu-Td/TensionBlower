/** 
 * @file   Charge.cpp
 * @brief  �G�l���M�[���ߏ���
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"

/*
 * �G�l���M�[���ߏ���
 */
void Player::Charge() {

	// �L�[���͏��擾
	int key = ApplicationMain::GetInstance()->GetKey();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5) && _energy < modeGame->_charaData->_maxEnergy) {
		if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
			if (!_isDash) {           // �_�b�V�����ĂȂ���Η��߉\
				_mvSpd = modeGame->_charaData->_mvSpdChrg;
				_isCharging = true;
			}
		}
	}
	else {
		_isCharging = false;
	}
}