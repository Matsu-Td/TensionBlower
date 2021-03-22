/**
 * @file   Boss.cpp
 * @brief  �{�X�֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/14
 */

#include "Boss.h"
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "ModeGameClear.h"
#include "BossBullet.h"
#include "BossBomb.h"
#include "BossAimShot.h"
#include "Sound.h"
#include "Destruction.h"
#include "BossVoice.h"
#include "Laser.h"

Boss* Boss::_pInstance = NULL;

Boss::Boss(){

	_pInstance = this;
	_mh = MV1LoadModel("res/model/boss/Tboss_model_mm.mv1");

	Initialize();
}

Boss::~Boss(){
	MV1DeleteModel(_mh);
}

/**
 * ������
 */
void Boss::Initialize() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	_vPos = VGet(0.0f, 0.5f, 0.0f);
	_vDir = VGet(0.0f, 0.0f, 0.0f);
	_attachIndex = 0;
	_totalTime = 0.0f;
	_state = STATE::NORMAL;

	_attachIndex = -1;
	_totalTime = 0.0f;
	_playTime = 0.0f;

	_shotPattern = 1;
	_shotAngle = -90.0f;
	_shotAngle1 = -90.0f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_reverseCnt = 60;
	_setRotAngle = 1.0f;
	_shotHeight = 0.0f;

	_hitpoint = CHARA_DATA->_boss.maxHP;
	_shield = CHARA_DATA->_boss.maxShield;
	_bulletNum = 0;
	_stateDown = false;
	_mlsDownFlag = false;
	_downTime = 0;
	_phase = 0;

	_deadCnt = 140;
	_deadFlag = false;

	_r = 10.0f;
}

/**
 * ���f�[�^�Đ�
 */
void Boss::PlayVoice(std::string voiceName) {
	PlaySoundMem(gBossVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/**
 * 6��ނ̐��f�[�^�������_���ŗ���
 */
void Boss::PlayAttackVoiceChange() {

	int voiceNo = rand() % ATTACK_VOICE_NUM;
	PlayVoice(_attackNameNo[voiceNo]);
}

/**
 * �e���p�^�[���ؑ֏���
 */
void Boss::ShotPatternSwitch() {

	// �t�F�[�Y���Ŕ�������e���p�^�[����3�Z�b�g�����_���ŕω�������
	if (_shotCnt % PATTERN_CHANGE_CNT == 0) {
		PlayAttackVoiceChange();       // ���f�[�^�Đ�
		_shotCnt = 0;                  // �J�E���g���Z�b�g
		_shotPattern = rand() % 3 + 1; // 3�p�^�[���������_���Ō���
	}

	// �t�F�[�Y���̒e���p�^�[���Z�b�g
	switch (_phase) {
	// �����t�F�[�Y
	case 0:                      
		if(_shotPattern <= 2){
			ShotPattern1and2();
			ShotPattern6();
			ShotPattern7();
		}
		else {
//			ShotPattern3();
			ShotPattern6();
			ShotPattern7();
		}
		break;
	// �t�F�[�Y1
	case 1:	                     
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern6();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
		}
		if (_shotPattern == 3) {
     		ShotPattern5();
		}
		break;
	// �t�F�[�Y2
	case 2:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern7();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	// �t�F�[�Y3
	case 3:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern6();
			LaserAttack2();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	// �t�F�[�Y4
	case 4:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern7();
			LaserAttack2();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
			LaserAttack2();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			ShotPattern6();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	}

	_shotCnt++;
}

/**
 * �e���p�^�[��1&2
 */
void Boss::ShotPattern1and2() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_shotCnt % 17 == 0 && _shotCnt != 1) {  
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, _shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		if (_shotPattern == 1) {
			_shotAngle += 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
		else if (_shotPattern == 2) {
			_shotAngle -= 2.0f;   // ���t���[�����ˊp�x��2�����炷
		}
	}
}

/**
 * �e���p�^�[��3
 */
void Boss::ShotPattern3() {

	_reverseCnt--;
	if (_reverseCnt <= 0) {
		_reverseCnt = SHOT_REVERSE_CNT;
		_setRotAngle *= -1.0f;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_shotCnt % 9 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.3f, _shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
		
	}
	else {
		_shotAngle += _setRotAngle;
	}
}

/**
 * �e���p�^�[��4-1
 */
void Boss::ShotPattern4_1() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 26 == 0) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 3.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, _shotAngle);
			modeGame->_objServer.Add(bullet); // �e����
			_shotAngle += 45.0f;              // �e���ˊp�x��45�������炷
		}
	}
	else {
		_shotAngle += 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/**
 * �e���p�^�[��4-2
 */
void Boss::ShotPattern4_2() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 26 == 13) {
		// ������8���e�𔭎˂���
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 5.0f;
			tmpPos.z = _vPos.z + sin(_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, _shotAngle1);
			modeGame->_objServer.Add(bullet); // �e����
			_shotAngle1 += 45.0f;             // �e���ˊp�x��45�������炷
		}
	}
	else {
		_shotAngle1 -= 2.0f;    // ���t���[�����ˊp�x��2�����炷
	}
}

/**
 * �e���p�^�[��5
 */
void Boss::ShotPattern5() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �v���C���[�ʒu�擾
	VECTOR plPos = Player::GetInstance()->GetPos();

	// ������7���e�𔭎˂���
	if (_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = _shotHeight;
		for (int i = 0; i < 7; i++) {
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = _vPos;
			tmpPos.y = abs(height) + 1.0f;         // �n�ォ�獂��1m����
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
			modeGame->_objServer.Add(bullet);      // �e����
			angleSide += 10.0f;                    // ���ˊp�x��10�������炷
			if (_shotHeight <= -12.0f) {
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
		_shotHeight += 3.0f;  // �e����ʒu��3m���㉺�ɕω�������
		if (abs(_shotHeight) >= 11.0f) {
			_shotHeight *= -1.0f;
		}
	}
}

/**
 * �e���p�^�[��6
 */
void Boss::ShotPattern6(){

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	VECTOR plPos = Player::GetInstance()->GetPos();
	if (_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // �e3�����̗��T�C�h�̒e���ˊp�x�����炷
		for (int i = 0; i < 3; i++) {
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = _vPos;
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
void Boss::ShotPattern7() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 48 == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.y = _vPos.y + 12.0f;
		BossBomb* bomb = NEW BossBomb(tmpPos);
		modeGame->_objServer.Add(bomb);
	}
}

/**
 * ���[�U�[�U��1-1
 */
void Boss::LaserAttack1_1() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 0.0f;
	if (_shotCnt == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
		tmpPos.y = 4.5f;
		tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * ���[�U�[�U��1-2
 */
void Boss::LaserAttack1_2() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 180.0f;
	if (_shotCnt == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
		tmpPos.y = 4.5f;
		tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, -2.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * ���[�U�[�U��2
 */
void Boss::LaserAttack2() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 45.0f;
	if (_shotCnt == 0) {
		// ������4�{�̃��[�U�[�𐶐�
		for (int i = 0; i < 4; i++) {
			VECTOR tmpPos = _vPos;
			tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
			Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
			modeGame->_objServer.Add(laser);
			laserAngle += 90.0f;  // ���[�U�[�Ԃ̊p�x
		}
	}
}

/**
 * �t�F�[�Y�ύX����
 */
void Boss::FhaseChange() {

	// �t�F�[�Y4�ֈڍs
	if (_hitpoint <= PHASE_FOUR_HP) {
		_phase = 4;
		return;
	}
	// �t�F�[�Y3�ֈڍs
	if (_hitpoint <= PHASE_THREE_HP) {
		_phase = 3;
		return;
	}
	// �t�F�[�Y2�ֈڍs
	if (_hitpoint <= PHASE_TWO_HP) {
		_phase = 2;
		return;
	}
	// �t�F�[�Y1�ֈڍs
	if (_hitpoint <= PHASE_ONE_HP) {
		_phase = 1;
		return;
	}
	// �����t�F�[�Y0
	_phase = 0;
}

/**
 * �_�E����ԏ���
 */
void Boss::StateDown(){

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// ���A
	if (_state == STATE::DOWN) {
		_mlsDownFlag = false;	   // �}���`���b�N�I���V�X�e���ɂ��_�E���t���O����
		_downTime--;               // �_�E�����ԃJ�E���g
		if (_downTime < 0) {
			// ���A���̐��f�[�^�Đ�
			PlayVoice("hukki");
			_downTime = 0;         // �_�E�����ԃ��Z�b�g
			_state = STATE::RETURN;// ���A��Ԃɂ�����
			_bulletNum = 0;        // �e�̐����Z�b�g
			_shield = CHARA_DATA->_boss.maxShield;  // �V�[���h�l�S��
		}
	}

	if (_shield > 0) {
		return;
	}
	// �_�E��
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // �_�E�����O�ɏo�����Ă����e�̐����J�E���g
			}
			int plEnergy = Player::GetInstance()->GetEnergy();            // �v���C���[�̃G�l���M�[���擾
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // �_�E�����Ԍv�Z                                           // �_�E����Ԃɂ���
			_state = STATE::DOWN;
		}
	}
}

/**
 * �Q�[���N���A����
 */
void Boss::Dead() {

	// �Q�[���N���A�����X�^�[�g
	if (_deadFlag) {
		_deadCnt--;
		if (_deadCnt == 0) {
			MV1DeleteModel(_mh); // �{�X���f�����폜����
		}
	}
	// �q�b�g�|�C���g�[���ŃQ�[���N���A�t���O�𗧂Ă�
	if (_hitpoint <= 0) {
		if (!_deadFlag) {
			// ���j���̐��f�[�^�Đ�
			PlayVoice("gekiha");
			VECTOR tmpPos = _vPos;
			tmpPos.y = 8.5f;
			Destruction* destruction = NEW Destruction(tmpPos);
			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Add(destruction);

		}
		_hitpoint = 0;
		_deadFlag = true;
	}
}

/**
 * �t���[�������F�v�Z
 */
void Boss::Process(){

	// �J�����̏�Ԃ��擾
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	STATE oldState = _state;

	// ���S����
	Dead();

	if (_deadFlag) {
		return;
	}
	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z

	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	if (_state == STATE::NORMAL) {

		// �e���U������
		if (_shield > 0) {
			// �}���`���b�N�I���V�X�e���������͒e�̔��ˑ��x��x������
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				if (_mlsCnt % 100 == 0) {
					ShotPatternSwitch();
				}
			}
			// �ʏ펞
			else {
				_mlsCnt = 0;
				ShotPatternSwitch();
			}
		}

		{  // �v���C���[����������Ƀ{�X�̐��ʂ�������
			VECTOR plPos = Player::GetInstance()->GetPos();
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;           // ���䂵�₷���悤�Ɉ�x���W�A���P�ʂ�x�P�ʂɕϊ�			
			float plAngle = (-deg - 90.0f) / 180.0f * DX_PI_F;  // 90�x���̂����␳���A���W�A���P�ʂɖ߂�
			// �p���x�������A�v���C���[������ʒu�ɂ������ƃ{�X�̐��ʂ�������
			if (plAngle > _vDir.y) {
				_vDir.y += ROT_SPD;
			}
			else if (plAngle < _vDir.y) {
				_vDir.y -= ROT_SPD;
			}
		}
	}

	// �t�F�[�Y�ؑ�
	FhaseChange();
	// �_�E������
	StateDown();

	if (oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::NORMAL:
			_attachIndex = -1; // �ʏ�̓��[�V��������
			break;
		case STATE::DOWN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "down"), -1, FALSE);
			break;
		case STATE::RETURN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "return"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}

/**
 * �t���[�������F�`��
 */
void Boss::Render(){

	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, _vDir);
	MV1DrawModel(_mh);

#if 0
	int y = 750;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Boss:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP�@    = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ����ޒl = %d", _shield);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �o�����Ă���e�̐� = %d", _bulletNum);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_�E������ = %d", _downTime);   y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  plangle = %f", a); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  _vDir.y = %f", _vDir.y); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ��� = %d", _state); y += size;
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}

/**
 * �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
 */
void Boss::RepelDamage() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// �V�[���h������Ƃ�
	if (_shield > 0) {  
		_hitpoint -= CHARA_DATA->_repelDmgHP;
		_shield -= CHARA_DATA->_repelDmgSld;

		if (_shield <= 0) {
			_shield = 0;
			_mlsDownFlag = true;  // �v���C���[�ɒe���Ԃ��ꂽ�e�ŃV�[���h���j�󂳂���true
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {            
		_hitpoint -= CHARA_DATA->_repelDmg;
	}
}

/**
 * �v���C���[����󂯂��_���[�W�ʌv�Z
 */
void Boss::AttackDamage(){

	// �_�E����Ԏ��̂ݔ�e���̐��f�[�^�Đ�
	if (_state == STATE::DOWN) {
		PlayVoice("hidan");
	}
	// �q�b�g���Đ�
	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);
	
	// �_���[�W�ʊi�[
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();
	// �V�[���h������Ƃ�
	if (_shield > 0) { 
		_hitpoint -= dmgHP;
		_shield -= dmgSld;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {            
		_hitpoint -= dmgNorm;
	}
}

/**
 * �q�b�g�|�C���g�ւ̔����_���[�W
 */
void Boss::ExplosionDamageHP(){
	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_hitpoint -= EXPLOSION_DMG_HP;
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		_hitpoint -= EXPLOSION_DMG_NORM;
	}
}

/**
 * �V�[���h�ւ̔����_���[�W
 */
void Boss::ExplosionDamageShield() {
	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_shield -= EXPLOSION_DMG_SLD;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
}
