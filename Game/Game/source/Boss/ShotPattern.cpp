/** 
 * @file   ShotPattern.cpp
 * @brief  �e���p�^�[������
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Boss.h"
#include "BossBullet.h"
#include "BossAimShot.h"
#include "BossBomb.h"
#include "../Effect/Laser.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::boss;

/*
 * �t�F�[�Y�ύX����
 */
void Boss::FhaseChange() {

	// �t�F�[�Y4�ֈڍs
	if (_hitpoint <= PHASE_FOUR_HP) {
		_phaseNo = 4;
		return;
	}
	// �t�F�[�Y3�ֈڍs
	if (_hitpoint <= PHASE_THREE_HP) {
		_phaseNo = 3;
		return;
	}
	// �t�F�[�Y2�ֈڍs
	if (_hitpoint <= PHASE_TWO_HP) {
		_phaseNo = 2;
		return;
	}
	// �t�F�[�Y1�ֈڍs
	if (_hitpoint <= PHASE_ONE_HP) {
		_phaseNo = 1;
		return;
	}
	// �����t�F�[�Y0
	_phaseNo = 0;
}

/*
 * �e���p�^�[���ؑ֏���
 */
void Boss::BarragePatternSwitch() {

	// �t�F�[�Y���Ŕ�������e���p�^�[����3�Z�b�g�����_���ŕω�������
	if (_shotCnt % PATTERN_CHANGE_CNT == 0) {
		PlayAttackVoiceChange();       // ���f�[�^�Đ�
		_shotCnt = 0;                  // �J�E���g���Z�b�g
		_patternRandom = rand() % 3 + 1; // 3�p�^�[���������_���Ō���
	}

	// �t�F�[�Y���̒e���p�^�[���Z�b�g
	switch (_phaseNo) {
		// �����t�F�[�Y
	case 0:
		if (_patternRandom <= 2) {
			BarragePattern1and2();
		}
		else {
			BarragePattern3();
		}
		break;
		// �t�F�[�Y1
	case 1:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern6();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
		}
		break;
		// �t�F�[�Y2
	case 2:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern7();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			BarragePattern6();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// �t�F�[�Y3
	case 3:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern6();
			LaserAttack2();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// �t�F�[�Y4
	case 4:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern7();
			LaserAttack2();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			BarragePattern6();
			LaserAttack2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			BarragePattern6();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	}

	_shotCnt++;
}

/*
 * �e���̒e�𐶐�����
 */
void Boss::ShotGeneration(float posY, float shotSpd, float shotAngle) {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame* > (::mode::ModeServer::GetInstance()->Get("game"));
	
	VECTOR tmpPos = { 0.0f,0.0f,0.0f };
	
	tmpPos.x = _vPos.x + cos(util::DegToRad(shotAngle)) * SHOT_DISTANCE;
	tmpPos.y = posY;
	tmpPos.z = _vPos.z + sin(util::DegToRad(shotAngle)) * SHOT_DISTANCE;

	BossBullet* bullet = NEW BossBullet(tmpPos, shotSpd, shotAngle);
	modeGame->_objServer.Add(bullet); // �e����
}

/*
 * ���[�U�[�𐶐�����
 */
void Boss::LaserGeneration(float laserAngle, float roteSpd) {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
	
	VECTOR tmpPos = _vPos;
	
	tmpPos.x = _vPos.x + cos(util::DegToRad(0)) * SHOT_DISTANCE;
	tmpPos.y = LESER_POS_Y;
	tmpPos.z = _vPos.z + sin(util::DegToRad(0)) * SHOT_DISTANCE;

	effect::Laser* laser = NEW effect::Laser(tmpPos, SHOT_DISTANCE, laserAngle, roteSpd);
	modeGame->_objServer.Add(laser);
}

/*
 * �e���p�^�[��1&2
 */
void Boss::BarragePattern1and2() {

	if (_shotCnt % 17 == 0 && _shotCnt != 1) {
		for (int i = 0; i < 8; i++) {
			ShotGeneration(4.5f, 1.0f, _shotAngle);  // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		if (_patternRandom == 1) {
			_shotAngle += 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
		else if (_patternRandom == 2) {
			_shotAngle -= 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
	}
}

/*
 * �e���p�^�[��3
 */
void Boss::BarragePattern3() {

	_reverseCnt--;
	if (_reverseCnt <= 0) {
		_reverseCnt = SHOT_REVERSE_CNT;
		_setRotAngle *= -1.0f;
	}

	if (_shotCnt % 9 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			ShotGeneration(4.5f, 1.3f, _shotAngle);  // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		_shotAngle += _setRotAngle;
	}
}

/*
 * �e���p�^�[��4-1
 */
void Boss::BarragePattern4_1() {

	if (_shotCnt % 26 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			ShotGeneration(3.5f, 1.2f, _shotAngle);  // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		_shotAngle += 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/*
 * �e���p�^�[��4-2
 */
void Boss::BarragePattern4_2() {

	if (_shotCnt % 26 == 13) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			ShotGeneration(5.0f, 1.2f, _shotAngleUp);  // �e����
			_shotAngleUp += 45.0f;             // �e���ˊp�x��45�������炷
		}
	}
	else {
		_shotAngleUp -= 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/*
 * �e���p�^�[��5
 */
void Boss::BarragePattern5() {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();

	// �v���C���[�ʒu�擾
	VECTOR plPos = player::Player::GetInstance()->GetPos();

	// ������7���e�𔭎˂���
	if (_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = _shotHeight;
		
		for (int i = 0; i < 7; i++) {
			float sx  = plPos.x - _vPos.x;
			float sz  = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = util::RadToDeg(rad);
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			
			tmpPos = _vPos;
			tmpPos.y = abs(height) + 1.0f;         // �n�ォ�獂��1m����
			
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
			modeGame->_objServer.Add(bullet);      // �e����
			angleSide += 10.0f;                    // ���ˊp�x��10�������炷
			
			if (_shotHeight <= -SHOT_Y_MAX) {
				height += 2.0f;    // �ׂ荇���e�ƒe�̍��፷
			}
			else {
				height -= 2.0f;    // �ׂ荇���e�ƒe�̍��፷
			}
			if (abs(height) >= static_cast<int>(SHOT_Y_MAX)) {
				height += abs(height) - SHOT_Y_MAX;
				height *= -1.0f;
			}
		}
		_shotHeight += 3.0f;  // �e����ʒu��3m���㉺�ɕω�������
		if (abs(_shotHeight) >= 11.0f) {
			_shotHeight *= -1.0f;
		}
	}
}

/*
 * �e���p�^�[��6
 */
void Boss::BarragePattern6() {

	VECTOR plPos = player::Player::GetInstance()->GetPos();
	if (_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // �e3�����̗��T�C�h�̒e���ˊp�x�����炷
		for (int i = 0; i < 3; i++) {
			float sx  = plPos.x - _vPos.x;
			float sz  = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = util::RadToDeg(rad);
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			
			tmpPos = _vPos;
			tmpPos.y = 3.5f;
			
			BossAimShot* bossAimShot = NEW BossAimShot(tmpPos, 1.5f, deg + angleSide);
			mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
			modeGame->_objServer.Add(bossAimShot); // �e����
			angleSide += 10.0f;                    // ���ˊp�x��10�������炷
		}
	}
}

/*
 * �e���p�^�[��7
 */
void Boss::BarragePattern7() {

	if (_shotCnt % 48 == 0) {
		VECTOR tmpPos = _vPos;
		
		tmpPos.y = _vPos.y + 12.0f;
		
		BossBomb* bomb = NEW BossBomb(tmpPos);
		mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
		modeGame->_objServer.Add(bomb);
	}
}

/*
 * ���[�U�[�U��1-1
 */
void Boss::LaserAttack1_1() {

	float laserAngle = 0.0f;  // ���[�U�[�̔��ˊp�x�A�ʒu
	if (_shotCnt == 0) {
		LaserGeneration(laserAngle);
	}
}

/*
 * ���[�U�[�U��1-2
 */
void Boss::LaserAttack1_2() {

	float laserAngle = 180.0f;  // ���[�U�[�̔��ˊp�x�A�ʒu
	if (_shotCnt == 0) {
		LaserGeneration(laserAngle, -2.0f);
	}
}

/*
 * ���[�U�[�U��2
 */
void Boss::LaserAttack2() {

	float laserAngle = 45.0f;  // ���[�U�[�̔��ˊp�x�A�ʒu
	if (_shotCnt == 0) {
		// ������4�{�̃��[�U�[�𐶐�
		for (int i = 0; i < 4; i++) {
			LaserGeneration(laserAngle);
			laserAngle += 90.0f;  // ���[�U�[�Ԃ̊p�x
		}
	}
}