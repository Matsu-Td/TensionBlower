/**
 * @file   PlayerEnergy.cpp
 * @brief  �v���C���[�G�l���M�[�֌W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerEnergy.h"

PlayerEnergy::PlayerEnergy() {

}

/**
 * �G�l���M�[�����
 */
void PlayerEnergy::CostEnergy(Player* player, float costEnergy) {
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
	float addEne;

	if (player->_energy > 0 || player->_energy < CHARA_DATA->_maxEnergy) {
		if (player->_swCharge) {               // �f�o�b�O�p
			if (oldState != player->_state) {
				// �W�����v(����)
				if (player->_state == Player::STATE::JUMP) {
					CostEnergy(player, CHARA_DATA->_egJump);
				}
				// �Z�����_�b�V��(����)
				if (player->_isShortDash) {
					CostEnergy(player, CHARA_DATA->_egDash);
				}
			}

			// �������_�b�V��(����)
			if (!player->_isShortDash && player->_isDash) {
				CostEnergy(player, 1);
			}

			// �}���`���b�N�I���V�X�e��(����)
			if (camState == Camera::STATE::MLS_LOCK) {
				CostEnergy(player, CHARA_DATA->_egMLS);
			}

			// �{�X�t�߂ōs������(��)
			if (player->_isNearBoss) {
				addEne = CHARA_DATA->_egAutoXArea;
			}
			else {
				addEne = 1.0f;
			}

			if (player->_energy >= CHARA_DATA->_maxEnergy) {
				return;
			}

			//�@����(��)
			if (player->_isCharging) {
				player->_energy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
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
				player->_energy += CHARA_DATA->_egAutoRec * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * addEne;
			}
		}
	}

	// MLS�ɂ��e���Ԃ��ŃV�[���h�j�󂵂��ꍇ�A[�{�X�̒e�̐� * �w��̃G�l���M�[��]���񕜂���
	if (Boss::GetInstance()->_mlsDownFlag) {
		player->_energy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	//�ŏ��G�l���M�[�l�I�[�o�[�h�~
	if (player->_energy < 0) {
		player->_energy = 0;
	}
	// �ő�G�l���M�[�l�I�[�o�[�h�~
	if (player->_energy > CHARA_DATA->_maxEnergy) { 
		player->_energy = CHARA_DATA->_maxEnergy;
	}
}