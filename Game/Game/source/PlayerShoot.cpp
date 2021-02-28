/**
 * @file   PlayerShoot.cpp
 * @brief  �v���C���[�ˌ��U��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerShoot.h"

/**
 * �ˌ��U�� (�Q�[���p�b�h�uRT�v�Ŏˌ�)
 */
void PlayerShoot::ShootingAttack(Player* player) {

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	// �Q�[���p�b�h�uRT�v
	int rt = dinput.Z;
	// RT�ŏ��l
	int rtMin = -100;

	if (rt < rtMin && !player->_isCharging && !player->_isZeroShot) { // ���ߏ�ԋy�ё��e�����[���ɂȂ����ꍇ�͎ˌ��s��
		if (player->_bulletNum == 0) {
			// �e��ł��؂��Ă��܂��ƃt���O������(= true) �� �ˌ��s��
			player->_isZeroShot = true;
		}
		if (player->_bulletNum > 0) {
			if (player->_canShot) {
				player->_state = Player::STATE::SHOT_ATCK;
				player->_isShooting = true;
				player->_playTime = 30.0f;
				player->_reloadTime = Player::RELOAD_TIME;	   // �����[�h�J�n���Ԃ��Z�b�g
				player->_canShot = false;
				player->_bulletNum--;
				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				PlayerBullet* bullet = NEW PlayerBullet();
				float angle = atan2(player->_vDir.z, player->_vDir.x);
				VECTOR tmp = player->_vPos;
				tmp.y = player->_vPos.y + 7.0f;
				bullet->SetPos(tmp);
				bullet->SetShotAngle(angle);
				modeGame->_objServer.Add(bullet);  // �e�����A�ˌ��J�n
			}
			else {
				player->_shotInterval--;
				if (player->_shotInterval == 0) {
					player->_canShot = true;
					player->_shotInterval = 10;      // ���̎ˌ��Ԋu��݂���
				}
			}
		}
	}
	else {
		// �ˌ����s��Ȃ���΃����[�h�J�n
		player->_isShooting = false;
		player->_reloadTime--;
		// �e��ł��؂����ꍇ�͑��������[�h�J�n
		if (player->_isZeroShot) {
			if (player->_bulletNum < Player::MAX_BULLET) {
				player->_bulletNum++;
			}
		}
		// �e���c���Ă����Ԃ������[�h�J�n���ԃ[���Ń����[�h�J�n
		else if (player->_reloadTime <= 0) {
			if (player->_bulletNum < Player::MAX_BULLET) {
				player->_bulletNum++;
			}
		}
	}
	// �����[�h������_shotZeroFlag����(= false)
	if (player->_bulletNum == Player::MAX_BULLET) {
		player->_isZeroShot = false;
	}
}