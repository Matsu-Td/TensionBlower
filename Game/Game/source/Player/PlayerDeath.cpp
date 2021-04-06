/** 
 * @file   PlayerDeath.cpp
 * @brief  �v���C���[�̎��S����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Mode/ModeGameOver.h"

 /*
  * ���S�������Q�[���I�[�o�[�ֈڍs
  */
void Player::Death() {

	// �Q�[���I�[�o�[
	if (_isGameOver) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = NEW ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	// �q�b�g�|�C���g 0 �ŃQ�[���I�[�o�[
	if (_hitpoint <= 0) {
		_state = STATE::DEATH;
		_isGameOver = true;
	}

	// ���S���[�V�����͒n��ōs��
	if (_state == STATE::DEATH) {
		// �d�͏���
		Gravity();
	}
}