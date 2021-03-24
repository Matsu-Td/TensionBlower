/**
 * @file   ShotPattern.cpp
 * @brief  �e���p�^�[������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "ShotPattern.h"
#include "ModeGame.h"
#include "BossBullet.h"
#include "BossAimShot.h"
#include "BossBomb.h"
#include "Laser.h"

 /**
  * �e���p�^�[���ؑ֏���
  */
void ShotPattern::ShotPatternSwitch(Boss* boss) {

	// �t�F�[�Y���Ŕ�������e���p�^�[����3�Z�b�g�����_���ŕω�������
	if (boss->_shotCnt % PATTERN_CHANGE_CNT == 0) {
		boss->PlayAttackVoiceChange();       // ���f�[�^�Đ�
		boss->_shotCnt = 0;                  // �J�E���g���Z�b�g
		boss->_shotPattern = rand() % 3 + 1; // 3�p�^�[���������_���Ō���
	}

	// �t�F�[�Y���̒e���p�^�[���Z�b�g
	switch (boss->_phase) {
		// �����t�F�[�Y
	case 0:
		if (boss->_shotPattern <= 2) {
			ShotPattern1and2(boss);
		}
		else {
			ShotPattern3(boss);
		}
		break;
		// �t�F�[�Y1
	case 1:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern6(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
		}
		break;
		// �t�F�[�Y2
	case 2:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern7(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			ShotPattern6(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
		// �t�F�[�Y3
	case 3:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern6(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
		// �t�F�[�Y4
	case 4:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern7(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			ShotPattern6(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			ShotPattern6(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
	}

	boss->_shotCnt++;
}

/**
 * �e���p�^�[��1&2
 */
void ShotPattern::ShotPattern1and2(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (boss->_shotCnt % 17 == 0 && boss->_shotCnt != 1) {
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			boss->_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		if (boss->_shotPattern == 1) {
			boss->_shotAngle += 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
		else if (boss->_shotPattern == 2) {
			boss->_shotAngle -= 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
	}
}

/**
 * �e���p�^�[��3
 */
void ShotPattern::ShotPattern3(Boss* boss) {

	boss->_reverseCnt--;
	if (boss->_reverseCnt <= 0) {
		boss->_reverseCnt = SHOT_REVERSE_CNT;
		boss->_setRotAngle *= -1.0f;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (boss->_shotCnt % 9 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.3f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			boss->_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}

	}
	else {
		boss->_shotAngle += boss->_setRotAngle;
	}
}

/**
 * �e���p�^�[��4-1
 */
void ShotPattern::ShotPattern4_1(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 26 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 3.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			boss->_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		boss->_shotAngle += 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/**
 * �e���p�^�[��4-2
 */
void ShotPattern::ShotPattern4_2(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 26 == 13) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 5.0f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, boss->_shotAngle1);
			modeGame->_objServer.Add(bullet); // �e����
			boss->_shotAngle1 += 45.0f;             // �e���ˊp�x��45�������炷
		}
	}
	else {
		boss->_shotAngle1 -= 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/**
 * �e���p�^�[��5
 */
void ShotPattern::ShotPattern5(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �v���C���[�ʒu�擾
	VECTOR plPos = Player::GetInstance()->GetPos();

	// ������7���e�𔭎˂���
	if (boss->_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = boss->_shotHeight;
		for (int i = 0; i < 7; i++) {
			float sx = plPos.x - boss->_vPos.x;
			float sz = plPos.z - boss->_vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = boss->_vPos;
			tmpPos.y = abs(height) + 1.0f;         // �n�ォ�獂��1m����
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
			modeGame->_objServer.Add(bullet);      // �e����
			angleSide += 10.0f;                    // ���ˊp�x��10�������炷
			if (boss->_shotHeight <= -12.0f) {
				height += 2.0f;    // �ׂ荇���e�ƒe�̍��፷
			}
			else {
				height -= 2.0f;    // �ׂ荇���e�ƒe�̍��፷
			}
			if (abs(height) >= 12) {
				height += abs(height) - 12.0f;
				height *= -1.0f;
			}
		}
		boss->_shotHeight += 3.0f;  // �e����ʒu��3m���㉺�ɕω�������
		if (abs(boss->_shotHeight) >= 11.0f) {
			boss->_shotHeight *= -1.0f;
		}
	}
}

/**
 * �e���p�^�[��6
 */
void ShotPattern::ShotPattern6(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	VECTOR plPos = Player::GetInstance()->GetPos();
	if (boss->_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // �e3�����̗��T�C�h�̒e���ˊp�x�����炷
		for (int i = 0; i < 3; i++) {
			float sx = plPos.x - boss->_vPos.x;
			float sz = plPos.z - boss->_vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = boss->_vPos;
			tmpPos.y = 3.5f;
			BossAimShot* bossAimShot = NEW BossAimShot(tmpPos, 1.5f, deg + angleSide);
			modeGame->_objServer.Add(bossAimShot);      // �e����
			angleSide += 10.0f;                    // ���ˊp�x��10�������炷
		}
	}
}

/**
 * �e���p�^�[��7
 */
void ShotPattern::ShotPattern7(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 48 == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.y = boss->_vPos.y + 12.0f;
		BossBomb* bomb = NEW BossBomb(tmpPos);
		modeGame->_objServer.Add(bomb);
	}
}

/**
 * ���[�U�[�U��1-1
 */
void ShotPattern::LaserAttack1_1(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 0.0f;
	if (boss->_shotCnt == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		tmpPos.y = 4.5f;
		tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * ���[�U�[�U��1-2
 */
void ShotPattern::LaserAttack1_2(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 180.0f;
	if (boss->_shotCnt == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
		tmpPos.y = 4.5f;
		tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, -2.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * ���[�U�[�U��2
 */
void ShotPattern::LaserAttack2(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 45.0f;
	if (boss->_shotCnt == 0) {
		// ������4�{�̃��[�U�[�𐶐�
		for (int i = 0; i < 4; i++) {
			VECTOR tmpPos = boss->_vPos;
			tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
			Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
			modeGame->_objServer.Add(laser);
			laserAngle += 90.0f;  // ���[�U�[�Ԃ̊p�x
		}
	}
}
