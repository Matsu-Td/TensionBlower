/** 
 * @file   ReticleGeneration.cpp
 * @brief  �Ə���������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/26
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Mode/ModeGame.h"
#include "Reticle.h"

 /*
  * �}���`���b�N�I���V�X�e���p�Ə��ǉ�
  */
void Player::ReticleGeneration() {

	// �L�[�̃g���K���擾	
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uLB�{�^���v�Ń}���`���b�N�I���V�X�e���p�Ə��ǉ�
	if (trg & PAD_INPUT_5) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
}