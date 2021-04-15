/** 
 * @file   ReticleGeneration.cpp
 * @brief  �Ə���������
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"
#include "Reticle.h"

using namespace tensionblower::player;

/*
 * �}���`���b�N�I���V�X�e���p�Ə��ǉ�
 */
void Player::ReticleGeneration() {

	// �L�[�̃g���K���擾	
	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	// �Q�[���p�b�h�uLB�{�^���v�Ń}���`���b�N�I���V�X�e���p�Ə��ǉ�
	if (trg & PAD_INPUT_5) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
}