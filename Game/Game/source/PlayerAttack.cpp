
/**
 * @file  PlayerAttack.cpp
 * @brief �v���C���[�ߐڍU������
 *
 * @date 2021-02-10
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerAttack.h"

PlayerAttack::PlayerAttack() {

}

void PlayerAttack::Initialize(){

}
 /**
  * ���ݔ������̋ߐڍU���_���[�W�ʂ��Z�b�g����
  */
void PlayerAttack::SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm) {

	player->_nowDmgHP = dmgHP;
	player->_nowDmgSld = dmgSld;
	player->_nowDmgNorm = dmgNorm;
}

/**
 * �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
 */
void PlayerAttack::SwitchAttackDamage(Player* player) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	switch (player->_state) {
	case Player::STATE::WEAK_ATCK1:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP1, CHARA_DATA->_wkDmgSld1, CHARA_DATA->_wkDmg1);
		break;
	case Player::STATE::WEAK_ATCK2:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP2, CHARA_DATA->_wkDmgSld2, CHARA_DATA->_wkDmg2);
		break;
	case Player::STATE::WEAK_ATCK3:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP3, CHARA_DATA->_wkDmgSld3, CHARA_DATA->_wkDmg3);
		break;
	case Player::STATE::WEAK_ATCK4:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP4, CHARA_DATA->_wkDmgSld4, CHARA_DATA->_wkDmg4);
		break;
	case Player::STATE::STRG_ATCK1:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP1, CHARA_DATA->_stDmgSld1, CHARA_DATA->_stDmg1);
		break;
	case Player::STATE::STRG_ATCK2:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP2, CHARA_DATA->_stDmgSld2, CHARA_DATA->_stDmg2);
		break;
	case Player::STATE::STRG_ATCK3:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP3, CHARA_DATA->_stDmgSld3, CHARA_DATA->_stDmg3);
		break;
	case Player::STATE::STRG_ATCK4:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP4, CHARA_DATA->_stDmgSld4, CHARA_DATA->_stDmg4);
		break;
	}
}

/**
 * ���ߐڍU���ւ̔h���֘A����
 */
void PlayerAttack::NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName) {

	if (player->_energy < attackEnergy) {                      // �G�l���M�[�c�ʃ`�F�b�N
		return;
	}
	player->_state = std::move(nextState);                     // ���̍U���̏�Ԃ֑J��
	player->_energy -= std::move(attackEnergy);                // �G�l���M�[����
	player->_atChargeFlag = false;                             // �U�����G�l���M�[���ߕs��
	player->_atChargeCnt = Player::AUTO_CHARGE_CNT;            // ���ߕ��A���ԃZ�b�g
	player->_attackCnt = player->_attackTotalTime[attackName]; // �U�����[�V�������ԃZ�b�g
	player->_receptionTime = RECEPTION_TIME;           // ���U����t���ԃZ�b�g
	player->_hitFlag = false;                                  // �{�X�ɍU�����������Ă��Ȃ�
	SwitchAttackDamage(player);                                // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
}

/**
 * ��ߐڍU���ւ̔h���֘A����
 */
void PlayerAttack::NextWeakAttack(Player* player, Player::STATE nextState, std::string attackName) {

	player->_state = std::move(nextState);                     // ���̍U���̏�Ԃ֑J��
	player->_attackCnt = player->_attackTotalTime[attackName]; // �U�����[�V�������ԃZ�b�g
	player->_receptionTime = RECEPTION_TIME;           // ���U����t���ԃZ�b�g
	player->_hitFlag = false;                                  // �{�X�ɍU�����������Ă��Ȃ�
	SwitchAttackDamage(player);                                // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
}


void PlayerAttack::AttackAction(Player* player) {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �U���J�E���g
	if (player->_attackCnt <= 0) {
		player->_attackCnt = 0;
		player->_hitFlag = false;
	}
	else {
		player->_attackCnt--;
	}

	// ��t����
	if (player->_attackCnt <= 20) {
		player->_receptionTime--;
	}
	if (player->_receptionTime <= 0) {
		player->_receptionTime = 0;
		player->_attackReloadTime = ATTACK_RELOAD_TIME;
		player->_attackFlag = false;
	}

	if (!player->_hitFlag) {
		if (player->_attackCnt >= 20 && player->_attackCnt < 35) {
			player->_canHitFlag = true;
		}
		else {
			player->_canHitFlag = false;
		}
	}

	switch (player->_state) {
	case Player::STATE::WEAK_ATCK1:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��2�֔h��
			if (trg & PAD_INPUT_4) {
				NextStrongAttack(player,CHARA_DATA->_egAtck2, Player::STATE::STRG_ATCK2, "strg_atck2");
			}
			// ��ߐڍU��2�֔h��
			else if (trg & PAD_INPUT_B) {
				NextWeakAttack(player, Player::STATE::WEAK_ATCK2, "weak_atck2");
			}
		}
		break;
	case Player::STATE::WEAK_ATCK2:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��3�֔h��
			if (trg & PAD_INPUT_4) {
				NextStrongAttack(player, CHARA_DATA->_egAtck3, Player::STATE::STRG_ATCK3, "strg_atck3");
			}
			// ��ߐڍU��3�֔h��
			else if (trg & PAD_INPUT_B) {
				NextWeakAttack(player, Player::STATE::WEAK_ATCK3, "weak_atck3");
			}
		}
		break;
	case Player::STATE::WEAK_ATCK3:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��4�֔h��
			if (trg & PAD_INPUT_4) {
				NextStrongAttack(player, CHARA_DATA->_egAtck4, Player::STATE::STRG_ATCK4, "strg_atck4");
			}
			// ��ߐڍU��4�֔h��
			else if (trg & PAD_INPUT_B) {
				NextWeakAttack(player, Player::STATE::WEAK_ATCK4, "weak_atck4");
			}
		}
		break;
		// �U���h���I���i��U��4,���U��1�`4�j
	case Player::STATE::WEAK_ATCK4:
	case Player::STATE::STRG_ATCK1:
	case Player::STATE::STRG_ATCK2:
	case Player::STATE::STRG_ATCK3:
	case Player::STATE::STRG_ATCK4:
		if (player->_attackCnt <= 0) {
			player->_attackFlag = false;               // �ߐڍU���I��
			player->_attackReloadTime = ATTACK_RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	}
}

/**
 * �ߐڍU������(����̂�)
 */
void PlayerAttack::FirstAttack(Player* player) {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_vPos.y == 0.0f && player->_attackReloadTime == 0) {
		if (trg & PAD_INPUT_2 && !player->_attackFlag) {
			player->_attackFlag = true;
			NextWeakAttack(player, Player::STATE::WEAK_ATCK1, "weak_atck1");

		}
		if (trg & PAD_INPUT_4 && !player->_attackFlag) {
			player->_attackFlag = true;
			NextStrongAttack(player, CHARA_DATA->_egAtck1, Player::STATE::STRG_ATCK1, "strg_atck1");
		}
	}
}

/**
 * �ߐڍU������(2���ڈȍ~)
 */
void PlayerAttack::SecondAttack(Player* player) {
	
	if (player->_attackFlag) {
		AttackAction(player);
	}
	if (player->_attackReloadTime > 0) {
		player->_attackReloadTime--;
	}
}