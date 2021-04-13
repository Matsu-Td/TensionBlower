/** 
 * @file   BossDeath.cpp
 * @brief  �{�X�̎��S����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"
#include "../Effect/Destruction.h"
#include "../Mode/ModeGame.h"

 /*
  * ���S����
  */
void Boss::Death() {

	// �{�X���폜
	if (_state == STATE::DEATH) {
		_deathCnt--;
		if (_deathCnt == 0) {
			MV1DeleteModel(_mh); // �{�X���f�����폜����
		}
	}
	// �q�b�g�|�C���g�[���ŃQ�[���N���A�t���O�𗧂Ă�
	if (_hitpoint <= 0) {
		if(_state != STATE::DEATH){
			// ���j���̐��f�[�^�Đ�
			PlayVoice("gekiha");
			VECTOR tmpPos = _vPos;
			tmpPos.y = 8.5f;

			Destruction* destruction = NEW Destruction(tmpPos);

			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Add(destruction);
		}
		_hitpoint = 0;
		_state = STATE::DEATH;
	}
}