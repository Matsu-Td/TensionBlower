/**
 * @file   PlayerAttack.cpp
 * @brief  �v���C���[�ߐڍU������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "PlayerAttack.h"
#include "../Sound/Sound.h"
#include "PlayerVoice.h"

/**
 * �U���������̐��f�[�^���Đ�����
 */
void PlayerAttack::PlayAttackVoice(std::string voiceName) {
	PlaySoundMem(gPlayerVoice._vc[voiceName], DX_PLAYTYPE_BACK);
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
		SetAttackDamage(player, modeGame->_charaData->_wkDmgHP1, modeGame->_charaData->_wkDmgSld1, modeGame->_charaData->_wkDmg1);
		break;
	case Player::STATE::WEAK_ATCK2:
		SetAttackDamage(player, modeGame->_charaData->_wkDmgHP2, modeGame->_charaData->_wkDmgSld2, modeGame->_charaData->_wkDmg2);
		break;
	case Player::STATE::WEAK_ATCK3:
		SetAttackDamage(player, modeGame->_charaData->_wkDmgHP3, modeGame->_charaData->_wkDmgSld3, modeGame->_charaData->_wkDmg3);
		break;
	case Player::STATE::WEAK_ATCK4:
		SetAttackDamage(player, modeGame->_charaData->_wkDmgHP4, modeGame->_charaData->_wkDmgSld4, modeGame->_charaData->_wkDmg4);
		break;
	case Player::STATE::STRG_ATCK1:
		SetAttackDamage(player, modeGame->_charaData->_stDmgHP1, modeGame->_charaData->_stDmgSld1, modeGame->_charaData->_stDmg1);
		break;
	case Player::STATE::STRG_ATCK2:
		SetAttackDamage(player, modeGame->_charaData->_stDmgHP2, modeGame->_charaData->_stDmgSld2, modeGame->_charaData->_stDmg2);
		break;
	case Player::STATE::STRG_ATCK3:
		SetAttackDamage(player, modeGame->_charaData->_stDmgHP3, modeGame->_charaData->_stDmgSld3, modeGame->_charaData->_stDmg3);
		break;
	case Player::STATE::STRG_ATCK4:
		SetAttackDamage(player, modeGame->_charaData->_stDmgHP4, modeGame->_charaData->_stDmgSld4, modeGame->_charaData->_stDmg4);
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
	PlaySoundMem(gSound._se["h_attack"], DX_PLAYTYPE_BACK);
	player->_state = std::move(nextState);                     // ���̍U���̏�Ԃ֑J��
	player->_energy -= std::move(attackEnergy);                // �G�l���M�[����
	player->_canAutoCharge = false;                            // ���ߐڍU�����̓G�l���M�[�����񕜒�~
	player->_autoChargeCnt = Player::AUTO_CHARGE_CNT;          // ���ߕ��A���ԃZ�b�g
	player->_attackCnt = player->_attackTotalTime[attackName]; // �U�����[�V�������ԃZ�b�g
	player->_receptionTime = RECEPTION_TIME;                   // ���U����t���ԃZ�b�g
	player->_hitFlag = false;                                  // �{�X�ɍU�����������Ă��Ȃ�
	SwitchAttackDamage(player);                                // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
}

/**
 * ��ߐڍU���ւ̔h���֘A����
 */
void PlayerAttack::NextWeakAttack(Player* player, Player::STATE nextState, std::string attackName) {

	PlaySoundMem(gSound._se["l_attack"], DX_PLAYTYPE_BACK);
	player->_state = std::move(nextState);                     // ���̍U���̏�Ԃ֑J��
	player->_attackCnt = player->_attackTotalTime[attackName]; // �U�����[�V�������ԃZ�b�g
	player->_receptionTime = RECEPTION_TIME;				   // ���U����t���ԃZ�b�g
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

	// �U����t����
	if (player->_attackCnt <= 20) {
		player->_receptionTime--;
	}
	if (player->_receptionTime <= 0) {
		player->_receptionTime = 0;
		player->_attackReloadTime = ATTACK_RELOAD_TIME;
		player->_isAttack = false;
	}


	// �ߐڍU���ؑ�
	switch (player->_state) {
	case Player::STATE::WEAK_ATCK1:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��2�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayAttackVoice("strong");
			    NextStrongAttack(player, modeGame->_charaData->_egAtck2, Player::STATE::STRG_ATCK2, "slash_h");
				SetStrongHitTime(player);
			}
			// ��ߐڍU��2�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��2�̐��f�[�^�Đ�
				PlayAttackVoice("weak2");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK2, "slash_l");
				SetWeakHitTime(player);
			}
		}
		break;
	case Player::STATE::WEAK_ATCK2:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��3�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayAttackVoice("strong");
				NextStrongAttack(player, modeGame->_charaData->_egAtck3, Player::STATE::STRG_ATCK3, "slash_h");
				SetStrongHitTime(player);
			}
			// ��ߐڍU��3�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��3�̐��f�[�^�Đ�
				PlayAttackVoice("weak3");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK3, "slash_l");
				SetWeakHitTime(player);
			}
		}
		break;
	case Player::STATE::WEAK_ATCK3:
		if (player->_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��4�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayAttackVoice("strong");
				NextStrongAttack(player, modeGame->_charaData->_egAtck4, Player::STATE::STRG_ATCK4, "slash_h");
				SetStrongHitTime(player);
			}
			// ��ߐڍU��4�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��4�̐��f�[�^�Đ�
				PlayAttackVoice("weak4");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK4, "slash_l");
				SetWeakHitTime(player);
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
			player->_canHitFlag = false;
			player->_isAttack = false;               // �ߐڍU���I��
			player->_attackReloadTime = ATTACK_RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	}

	// �ߐڍU�������蔻�蔭��
	if (!player->_hitFlag) {
		if (player->_attackCnt >= player->_hitEnd && player->_attackCnt < player->_hitStart) {
			player->_canHitFlag = true;
		}
		else {
			player->_canHitFlag = false;
		}
	}
}

/**
 * �ߐڍU������(����̂�)
 */
void PlayerAttack::FirstAttack(Player* player) {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_vPos.y == 0.0f && player->_attackReloadTime == 0) {
		if (trg & PAD_INPUT_2 && !player->_isAttack) {
			// ��ߐڍU��1�̐��f�[�^�Đ�
			PlayAttackVoice("weak1");

			player->_isAttack = true;
			NextWeakAttack(player, Player::STATE::WEAK_ATCK1, "slash_l");
			SetWeakHitTime(player);

		}
		if (trg & PAD_INPUT_4 && !player->_isAttack) {
			// ���ߐڍU���̐��f�[�^�Đ�
			PlayAttackVoice("strong");

			player->_isAttack = true;
			NextStrongAttack(player, modeGame->_charaData->_egAtck1, Player::STATE::STRG_ATCK1, "slash_h");
			SetStrongHitTime(player);
		}
	}
}

/**
 * �ߐڍU������(2���ڈȍ~)
 */
void PlayerAttack::SecondAttack(Player* player) {
	
	if (player->_isAttack) {
		AttackAction(player);
	}
	if (player->_attackReloadTime > 0) {
		player->_attackReloadTime--;
	}
}

/**
 * ��ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
 */
void PlayerAttack::SetWeakHitTime(Player* player){
	player->_hitStart = 35;
	player->_hitEnd = 20;
}

/**
 * ���ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
 */
void PlayerAttack::SetStrongHitTime(Player* player) {
	player->_hitStart = 60;
	player->_hitEnd = 50;
}
