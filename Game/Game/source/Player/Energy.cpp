/**
 * @file   Energy.cpp
 * @brief  �v���C���[�G�l���M�[�֌W����
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"

/*
 * �G�l���M�[�����
 */
void Player::CostEnergy(int costEnergy) {

	_canAutoCharge = false;
	_autoChargeCnt = Player::AUTO_CHARGE_CNT;
	_energy -= costEnergy;
}

/*
 * �{�X�Ƃ̋������m�F(�����񕜗p)
 */
void Player::CheckDistanceToBoss() {

	// �{�X�ʒu���擾
	VECTOR bsPos = Boss::GetInstance()->GetPos();
	float dx = _vPos.x - bsPos.x;
	float dz = _vPos.z - bsPos.z;
	float len = sqrt(dx * dx + dz * dz);
	_bsAngle = atan2(dz, dx);
	// �{�X�Ƃ̋�����50m�ȉ����ǂ���
	if (len <= 50) {
		_isNearBoss = true;
	}
	else {
		_isNearBoss = false;
	}
}

/*
 * �G�l���M�[�̉񕜁A�����
 */
void Player::EnergyManager() {

	// �J�����̏�Ԏ擾
	Camera::STATE camState = Camera::GetInstance()->GetState();
	
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	int addEne;
	
	// �{�X�Ƃ̋������m�F
	CheckDistanceToBoss();

	if (_energy > 0 || _energy < modeGame->_charaData->_maxEnergy) {

		if (_oldState != _state) {
			// �W�����v(����)
			if (_state == Player::STATE::JUMP) {
				CostEnergy(modeGame->_charaData->_egJump);
			}
			// �Z�����_�b�V��(����)
			if (_isShortDash) {
				CostEnergy(modeGame->_charaData->_egDash);
			}
		}

		// �������_�b�V��(����)
		if (!_isShortDash && _isDash) {
			CostEnergy(1);
		}

		// �}���`���b�N�I���V�X�e��(����)
		if (camState == Camera::STATE::MLS_LOCK) {
			CostEnergy(modeGame->_charaData->_egMLS);
		}

		// �{�X�t�߂ōs������(��)
		if (_isNearBoss) {
			addEne = modeGame->_charaData->_egAutoXArea;
		}
		else {
			addEne = 1;
		}

		if (_energy >= modeGame->_charaData->_maxEnergy) {
			return;
		}

		//�@����(��)
		if (_isCharging) {
			_energy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
		}

		// �����񕜊J�n�̃C���^�[�o��
		if (!_canAutoCharge) {
			_autoChargeCnt--;
			if (_autoChargeCnt <= 0) {   // ���̎����񕜊J�n�Ԋu��݂���
				_autoChargeCnt = 0;
				_canAutoCharge = true;
			}
		}
		// ������(��)
		else if (!_isCharging) {
			_energy += modeGame->_charaData->_egAutoRec * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * addEne;
		}

	}

	// MLS�ɂ��e���Ԃ��ŃV�[���h�j�󂵂��ꍇ�A[�{�X�̒e�̐� * �w��̃G�l���M�[��]���񕜂���
	if (Boss::GetInstance()->_mlsDownFlag) {
		_energy += (modeGame->_charaData->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (modeGame->_charaData->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	//�ŏ��G�l���M�[�l�I�[�o�[�h�~
	if (_energy < 0) {
		_energy = 0;
	}
	// �ő�G�l���M�[�l�I�[�o�[�h�~
	if (_energy > modeGame->_charaData->_maxEnergy) {
		_energy = modeGame->_charaData->_maxEnergy;
	}
}