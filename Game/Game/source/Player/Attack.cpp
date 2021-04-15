/**
 * @file   Attack.cpp
 * @brief  �v���C���[�ߐڍU������
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"
#include "../Sound/Sound.h"

using namespace tensionblower::player;

/*
 * ���ݔ������̋ߐڍU���_���[�W�ʂ��Z�b�g����
 */
void Player::SetAttackDamage(int dmgHP, int dmgSld, int dmgNorm) {

	_nowDmgHP = dmgHP;
	_nowDmgSld = dmgSld;
	_nowDmgNorm = dmgNorm;
}

/*
 * �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
 */
void Player::SwitchAttackDamage() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	switch (_state) {
	case Player::STATE::WEAK_ATCK1:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP1, modeGame->_charaData->_wkDmgSld1, modeGame->_charaData->_wkDmg1);
		break;
	case Player::STATE::WEAK_ATCK2:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP2, modeGame->_charaData->_wkDmgSld2, modeGame->_charaData->_wkDmg2);
		break;
	case Player::STATE::WEAK_ATCK3:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP3, modeGame->_charaData->_wkDmgSld3, modeGame->_charaData->_wkDmg3);
		break;
	case Player::STATE::WEAK_ATCK4:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP4, modeGame->_charaData->_wkDmgSld4, modeGame->_charaData->_wkDmg4);
		break;
	case Player::STATE::STRG_ATCK1:
		SetAttackDamage(modeGame->_charaData->_stDmgHP1, modeGame->_charaData->_stDmgSld1, modeGame->_charaData->_stDmg1);
		break;
	case Player::STATE::STRG_ATCK2:
		SetAttackDamage(modeGame->_charaData->_stDmgHP2, modeGame->_charaData->_stDmgSld2, modeGame->_charaData->_stDmg2);
		break;
	case Player::STATE::STRG_ATCK3:
		SetAttackDamage(modeGame->_charaData->_stDmgHP3, modeGame->_charaData->_stDmgSld3, modeGame->_charaData->_stDmg3);
		break;
	case Player::STATE::STRG_ATCK4:
		SetAttackDamage(modeGame->_charaData->_stDmgHP4, modeGame->_charaData->_stDmgSld4, modeGame->_charaData->_stDmg4);
		break;
	}
}

/*
 * ���ߐڍU���ւ̔h���֘A����
 */
void Player::NextStrongAttack(int attackEnergy, STATE nextState, std::string attackName) {

	if (_energy < attackEnergy) {                      // �G�l���M�[�c�ʃ`�F�b�N
		return;
	}

	PlaySoundMem(gSound._se["h_attack"], DX_PLAYTYPE_BACK);

	_state = std::move(nextState);                  // ���̍U���̏�Ԃ֑J��
	_energy -= std::move(attackEnergy);             // �G�l���M�[����
	_canAutoCharge = false;                         // ���ߐڍU�����̓G�l���M�[�����񕜒�~
	_autoChargeCnt = Player::AUTO_CHARGE_CNT;       // ���ߕ��A���ԃZ�b�g
	_attackCnt = _mapAttackTotalTime[attackName];   // �U�����[�V�������ԃZ�b�g
	_receptionTime = RECEPTION_TIME;                // ���U����t���ԃZ�b�g
	_hitFlag = false;                               // �{�X�ɍU�����������Ă��Ȃ�

	SwitchAttackDamage();                           // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
}

/*
 * ��ߐڍU���ւ̔h���֘A����
 */
void Player::NextWeakAttack(STATE nextState, std::string attackName) {

	PlaySoundMem(gSound._se["l_attack"], DX_PLAYTYPE_BACK);

	_state = std::move(nextState);                  // ���̍U���̏�Ԃ֑J��
	_attackCnt = _mapAttackTotalTime[attackName];   // �U�����[�V�������ԃZ�b�g
	_receptionTime = RECEPTION_TIME;			    // ���U����t���ԃZ�b�g
	_hitFlag = false;                               // �{�X�ɍU�����������Ă��Ȃ�

	SwitchAttackDamage();                           // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
}

/*
 * �e�ߐڍU���ւ̃L�[���͏���
 */
void Player::AttackAction() {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();
	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	// �U���J�E���g
	if (_attackCnt <= 0) {
		_attackCnt = 0;
		_hitFlag = false;
	}
	else {
		_attackCnt--;
	}

	// �U����t����
	if (_attackCnt <= 20) {
		_receptionTime--;
	}
	if (_receptionTime <= 0) {
		_receptionTime = 0;
		_attackReloadTime = ATTACK_RELOAD_TIME;
		_isAttack = false;
	}


	// �ߐڍU���ؑ�
	switch (_state) {
	case Player::STATE::WEAK_ATCK1:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��2�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck2, Player::STATE::STRG_ATCK2, "slash_h");
				SetStrongHitTime();
			}
			// ��ߐڍU��2�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��2�̐��f�[�^�Đ�
				PlayVoice("weak2");

				NextWeakAttack(STATE::WEAK_ATCK2, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
	case Player::STATE::WEAK_ATCK2:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��3�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck3, Player::STATE::STRG_ATCK3, "slash_h");
				SetStrongHitTime();
			}
			// ��ߐڍU��3�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��3�̐��f�[�^�Đ�
				PlayVoice("weak3");

				NextWeakAttack(STATE::WEAK_ATCK3, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
	case Player::STATE::WEAK_ATCK3:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��4�֔h��
			if (trg & PAD_INPUT_4) {
				// ���ߐڍU���̐��f�[�^�Đ�
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck4, Player::STATE::STRG_ATCK4, "slash_h");
				SetStrongHitTime();
			}
			// ��ߐڍU��4�֔h��
			else if (trg & PAD_INPUT_B) {
				// ��ߐڍU��4�̐��f�[�^�Đ�
				PlayVoice("weak4");

				NextWeakAttack(STATE::WEAK_ATCK4, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
		// �U���h���I���i��U��4,���U��1�`4�j
	case Player::STATE::WEAK_ATCK4:
	case Player::STATE::STRG_ATCK1:
	case Player::STATE::STRG_ATCK2:
	case Player::STATE::STRG_ATCK3:
	case Player::STATE::STRG_ATCK4:
		if (_attackCnt <= 0) {
			_canHitFlag = false;
			_isAttack = false;               // �ߐڍU���I��
			_attackReloadTime = ATTACK_RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	}

	// �ߐڍU�������蔻�蔭��
	if (!_hitFlag) {
		if (_attackCnt >= _hitEndCnt && _attackCnt < _hitStartCnt) {
			_canHitFlag = true;
		}
		else {
			_canHitFlag = false;
		}
	}
}

/*
 * �ߐڍU������(����̂�)
 */
void Player::FirstAttack() {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (_vPos.y == 0.0f && _attackReloadTime == 0) {
		if (trg & PAD_INPUT_2 && !_isAttack) {
			// ��ߐڍU��1�̐��f�[�^�Đ�
			PlayVoice("weak1");

			_isAttack = true;
			NextWeakAttack(STATE::WEAK_ATCK1, "slash_l");
			SetWeakHitTime();

		}
		if (trg & PAD_INPUT_4 && !_isAttack) {
			// ���ߐڍU���̐��f�[�^�Đ�
			PlayVoice("strong");

			_isAttack = true;

			mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
		
			NextStrongAttack(modeGame->_charaData->_egAtck1, STATE::STRG_ATCK1, "slash_h");
			SetStrongHitTime();
		}
	}
}

/*
 * �ߐڍU������(2���ڈȍ~)
 */
void Player::SecondAttack() {

	if (_isAttack) {
		AttackAction();
	}
	if (_attackReloadTime > 0) {
		_attackReloadTime--;
	}
}

/*
 * ��ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
 */
void Player::SetWeakHitTime() {
	_hitStartCnt = 35;
	_hitEndCnt   = 20;
}

/*
 * ���ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
 */
void Player::SetStrongHitTime() {
	_hitStartCnt = 60;
	_hitEndCnt   = 50;
}
