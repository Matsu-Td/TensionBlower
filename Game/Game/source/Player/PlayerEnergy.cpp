/**
 * @file   PlayerEnergy.cpp
 * @brief  �v���C���[�G�l���M�[�֌W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "PlayerEnergy.h"

PlayerEnergy::PlayerEnergy() {

}

/**
 * �G�l���M�[�����
 */
void PlayerEnergy::CostEnergy(Player* player, int costEnergy) {
	player->_canAutoCharge = false;
	player->_autoChargeCnt = Player::AUTO_CHARGE_CNT;
	player->_energy -= costEnergy;
}

/**
 * �G�l���M�[�Ǘ�
 */
void PlayerEnergy::EnergyManager(Player* player, Player::STATE oldState) {

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	int addEne;

	if (player->_energy > 0 || player->_energy < modeGame->_charaData->_maxEnergy) {

		if (oldState != player->_state) {
			// �W�����v(����)
			if (player->_state == Player::STATE::JUMP) {
				CostEnergy(player, modeGame->_charaData->_egJump);
			}
			// �Z�����_�b�V��(����)
			if (player->_isShortDash) {
				CostEnergy(player, modeGame->_charaData->_egDash);
			}
		}

		// �������_�b�V��(����)
		if (!player->_isShortDash && player->_isDash) {
			CostEnergy(player, 1);
		}

		// �}���`���b�N�I���V�X�e��(����)
		if (camState == Camera::STATE::MLS_LOCK) {
			CostEnergy(player, modeGame->_charaData->_egMLS);
		}

		// �{�X�t�߂ōs������(��)
		if (player->_isNearBoss) {
			addEne = modeGame->_charaData->_egAutoXArea;
		}
		else {
			addEne = 1;
		}

		if (player->_energy >= modeGame->_charaData->_maxEnergy) {
			return;
		}

		//�@����(��)
		if (player->_isCharging) {
			player->_energy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
		}

		// �����񕜊J�n�̃C���^�[�o��
		if (!player->_canAutoCharge) {
			player->_autoChargeCnt--;
			if (player->_autoChargeCnt <= 0) {   // ���̎����񕜊J�n�Ԋu��݂���
				player->_autoChargeCnt = 0;
				player->_canAutoCharge = true;
			}
		}
		// ������(��)
		else if (!player->_isCharging) {
			player->_energy += modeGame->_charaData->_egAutoRec * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * addEne;
		}

	}

	// MLS�ɂ��e���Ԃ��ŃV�[���h�j�󂵂��ꍇ�A[�{�X�̒e�̐� * �w��̃G�l���M�[��]���񕜂���
	if (Boss::GetInstance()->_mlsDownFlag) {
		player->_energy += (modeGame->_charaData->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (modeGame->_charaData->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	//�ŏ��G�l���M�[�l�I�[�o�[�h�~
	if (player->_energy < 0) {
		player->_energy = 0;
	}
	// �ő�G�l���M�[�l�I�[�o�[�h�~
	if (player->_energy > modeGame->_charaData->_maxEnergy) {
		player->_energy = modeGame->_charaData->_maxEnergy;
	}
}