/** 
 * @file   Down.cpp
 * @brief  �{�X�̃_�E������
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

using namespace tensionblower::boss;

/*
 * �_�E������
 */
void Boss::StateDown() {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();

	// ���A
	if (_state == STATE::DOWN) {
		_vPos.y = 0.0f;
		_mlsDownFlag = false;	   // �}���`���b�N�I���V�X�e���ɂ��_�E���t���O����
		_downTime--;               // �_�E�����ԃJ�E���g
		if (_downTime < 0) {
			// ���A���̐��f�[�^�Đ�
			PlayVoice("hukki");
			_downTime = 0;         // �_�E�����ԃ��Z�b�g
			_state = STATE::RETURN;// ���A��Ԃɂ�����
			_bulletNum = 0;        // �e�̐����Z�b�g
			_shield = modeGame->_charaData->_boss.maxShield;  // �V�[���h�l�S��
		}
	}

	if (_shield > 0) {
		return;
	}
	// �_�E��
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);

		for (auto&& itr : *modeGame->_objServer.List()) {
			if (itr->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // �_�E�����O�ɏo�����Ă����e�̐����J�E���g
			}
			int plEnergy = player::Player::GetInstance()->GetEnergy();            // �v���C���[�̃G�l���M�[���擾
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // �_�E�����Ԍv�Z                                           // �_�E����Ԃɂ���
			_state = STATE::DOWN;
		}
	}
}