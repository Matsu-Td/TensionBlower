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

using namespace tensionblower::player;

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
	VECTOR bsPos = boss::Boss::GetInstance()->GetPos();
	float sx = _vPos.x - bsPos.x;
	float sz = _vPos.z - bsPos.z;
	float length = Util::Sqrt(sx, sz);

	_bsAngle = atan2(sz, sx);

	// �{�X�Ƃ̋�����50m�ȉ����ǂ���
	if (length <= 50) {
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
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();
	
	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	// �{�X�Ƃ̋������m�F
	CheckDistanceToBoss();

	if (_energy > 0 || _energy < modeGame->_charaData->_maxEnergy) {
		int addEne;

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
		if (camState == camera::Camera::STATE::MLS_LOCK) {
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
	if (boss::Boss::GetInstance()->_mlsDownFlag) {
		_energy += (modeGame->_charaData->_egShotNum * boss::Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (modeGame->_charaData->_egShotNum * boss::Boss::GetInstance()->_bulletNum);
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