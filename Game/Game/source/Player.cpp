
/**
 * @file  Player.cpp
 * @brief �v���C���[�֘A����
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"
#include "BulletServer.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "Reticle.h"

Player* Player::_pInstance = NULL;

Player::Player(){

	_pInstance = this;

	_mh = MV1LoadModel("res/model/���f�[�^/TB_player_mm01.mv1");
	Initialize();
	_attack->Initialize();
}

Player::~Player(){
}

/**
 * ������
 */
void Player::Initialize(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = CHARA_DATA->_mvSpdNorm;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.0f;
	_jumpTime = 0.0f;
	_isCanJump = true;
	_isCharging = false;
	_isShortDash = false;
	_isCanLongDash = false;
	_isDash = false;

	// �ȉ��X�e�[�^�X��
	// �ˌ�
	_bulletNum = MAX_BULLET;
	_canShotFlag = true;
	_shotInterval = 5;
	_reloadTime = RELOAD_TIME;
	_shotZeroFlag = false;

	// �G�l���M�[
	_energy = CHARA_DATA->_maxEnergy;
	_atChargeFlag = true;
	_atChargeCnt = 30;

	// �q�b�g�|�C���g
	_hitpoint = CHARA_DATA->_maxHP;

	_gameOverCnt = 60;
	_gameOverFlag = false;

	_camStateMLS = false;

	_swCharge = true;

	_shotFlag = false;

	_attackFlag = false;
	_attackCnt = 0;
	_receptionTime = 0;
	_attackReloadTime = 0;
	_hitFlag = false;
	_canHitFlag = false;

	// �e�ߐڍU���̃A�j���[�V�������Đ����Ԃ��i�[
	for (int i = 0; i < ATTACK_NUM; i++) {
	_attackTotalTime[AttackName[i]] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	}
}

 
void Player::JumpAction() {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_energy >= CHARA_DATA->_egJump) {
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
			_mvSpd = CHARA_DATA->_mvSpdNorm;
			_jumpTime = 0.f;
		}
	}
	if (!_isCanJump) {
		float inVel = 4.0f;
		_vPos.y = inVel * _jumpTime - 0.5f * GRAVITY * _jumpTime * _jumpTime;
	}
	
	_jumpTime += 0.2f;

	if (_vPos.y < GROUND_Y) {
		_vPos.y = GROUND_Y;
		if (_isCharging == false) {
			_isCanJump = true;
		}
	}
}

/**
 * �J�������b�N���̈ړ��A�_�b�V�����[�V�����ؑ֏���
 * ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
 */
void Player::LeftAnalogDeg(float length){

	if (!_isCanJump) {
		return;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_isDash) {
		// �_�b�V���p�ړ����x�Z�b�g
		_mvSpd = CHARA_DATA->_mvSpdDash;
		// �O�����_�b�V���ړ�
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = STATE::FOR_DASH;
		}
		// �������_�b�V���ړ�
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = STATE::LEFT_DASH;
		}
		// �E�����_�b�V���ړ�
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = STATE::RIGHT_DASH;
		}
		// ������_�b�V���ړ�
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER && length >= 0.3f) {
			_state = STATE::BACK_DASH;
		}
		//   // ���͂��Q�[���p�b�h�uRB�v�̂ݏꍇ�͑O�����_�b�V���ړ�
		else {
			_state = STATE::FOR_DASH;
		}
	}
	else {
		// �ʏ�ړ����x�Z�b�g
		_mvSpd = CHARA_DATA->_mvSpdNorm;
		// �O�����ړ�
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = STATE::WALK;
		}
		// �������ړ�
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = STATE::LEFT_MOVE;
		}
		// �E�����ړ�
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = STATE::RIGHT_MOVE;
		}
		// ������ړ�
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER) {
			_state = STATE::BACK_MOVE;
		}
	}
}


/**
 * �ˌ��U�� (�Q�[���p�b�h�uRT�v�Ŏˌ�)
 */
void Player::ShotAttack(float rt) {

	int rtMin = -100;  // RT�ŏ��l
	if (rt < rtMin && !_isCharging && !_shotZeroFlag) { // ���ߏ�ԋy�ё��e�����[���ɂȂ����ꍇ�͎ˌ��s��
		if (_bulletNum == 0) {
			_shotZeroFlag = true;      // �e��ł��؂��Ă��܂��ƃt���O������(= true) �� �ˌ��s��
		}
		if (_bulletNum > 0) {
			if (_canShotFlag) {
				_state = STATE::SHOT_ATCK;
				_shotFlag = true;
				_playTime = 30.0f;
				_reloadTime = RELOAD_TIME;	   // �����[�h�J�n���Ԃ��Z�b�g
				_canShotFlag = false;
				_bulletNum--;
				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				PlayerBullet* bullet = NEW PlayerBullet();
				float angle = atan2(_vDir.z, _vDir.x);
				VECTOR tmp = _vPos;
				tmp.y = _vPos.y + 5.5f;
				bullet->SetPos(tmp);
				bullet->SetShotAngle(angle);
				modeGame->_objServer.Add(bullet);  // �e�����A�ˌ��J�n
			}
			else {
				_shotInterval--;
				if (_shotInterval == 0) {
					_canShotFlag = true;
					_shotInterval = 10;      // ���̎ˌ��Ԋu��݂���
				}
			}

		}
	}
	else {             // �ˌ����s��Ȃ���΃����[�h�J�n
		_shotFlag = false;
		_reloadTime--;
		if (_shotZeroFlag) {            // �e��ł��؂����ꍇ�͑��������[�h�J�n
			if (_bulletNum < MAX_BULLET) {
				_bulletNum++;
			}
		}
		else if (_reloadTime <= 0) {    // �e���c���Ă����Ԃ������[�h�J�n���ԃ[���Ń����[�h�J�n
			if (_bulletNum < MAX_BULLET) {
				_bulletNum++;
			}
		}
	}
	if (_bulletNum == MAX_BULLET) {
		_shotZeroFlag = false;          // �����[�h������_shotZeroFlag����(= false)
	}
}

/**
 * ����G�l���M�[����
 */
void Player::CostEnergy(float costEnergy) {
	_atChargeFlag = false;
	_atChargeCnt = AUTO_CHARGE_CNT;
	_energy -= costEnergy;
}

/**
 * �G�l���M�[�Ǘ�
 */
void Player::EnergyManager(STATE oldState){

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float addEne;

	if (_energy > 0 || _energy < CHARA_DATA->_maxEnergy) {
		if (_swCharge) {               // �f�o�b�O�p
			if (oldState != _state) {
				// �W�����v(����)
				if (_state == STATE::JUMP) {
					CostEnergy(CHARA_DATA->_egJump);
				}
				// �Z�����_�b�V��(����)
				if (_isShortDash) {
					CostEnergy(CHARA_DATA->_egDash);
				}
			}

			// �������_�b�V��(����)
			if (!_isShortDash && _isDash) {
				CostEnergy(1);
			}

			// �}���`���b�N�I���V�X�e��(����)
			if (camState == Camera::STATE::MLS_LOCK) {
				CostEnergy(CHARA_DATA->_egMLS);
			}

			// �{�X�t�߂ōs������(��)
			if (_nearPosFlag) {
				addEne = CHARA_DATA->_egAutoXArea;
			}
			else {
				addEne = 1.0f;
			}

			if (_energy >= CHARA_DATA->_maxEnergy) {
				return;
			}
			//�@����(��)
			if (_isCharging) {
				_energy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
			}

			// �����񕜊J�n�̃C���^�[�o��
			if (!_atChargeFlag) {
				_atChargeCnt--;
				if (_atChargeCnt <= 0) {   // ���̎����񕜊J�n�Ԋu��݂���
					_atChargeCnt = 0;
					_atChargeFlag = true;
				}
			}
			// ������(��)
			else if (!_isCharging) {
				_energy += CHARA_DATA->_egAutoRec * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * addEne;
			}
		}
	}
	if (_energy < 0) {
		_energy = 0;
	}
	if (_energy > CHARA_DATA->_maxEnergy) {  // �G�l���M�[�񕜎��ɍő�G�l���M�[�l�𒴂���̂�h��
		_energy = CHARA_DATA->_maxEnergy;
	}
}

/**
 * �����蔻��
 */
void Player::Collision() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// �X�e�[�W�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 2.0f) == true) {
				VECTOR slideVec;
				slideVec = VCross(_vDir, (*itr)->_hitPolyDim.Dim->Normal);
				slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
				_vPos = VAdd(_oldPos, slideVec);
				_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.5f));
			}
		}
		// �{�X�̒e�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
			// ���e
			if (IsHitLineSegment(*(*itr), 1.5f)) {
				modeGame->_objServer.Del(*itr);
				_hitpoint -= CHARA_DATA->_boss.shotDmg;
			}
			// �J�X������(�G�l���M�[��)
			if (IsHitLineSegment(*(*itr), 2.5f)) {
				_energy += CHARA_DATA->_egAvoid;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAvoid;
			}
			if (Boss::GetInstance()->_mlsDownFlag) {
				modeGame->_objServer.Del(*itr);
			}
		}
		// �{�X�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitArc_Sphere(*(*itr)) == true) {
				if (_canHitFlag && !_hitFlag) {
					_hitFlag = true;
					(*itr)->AttackDamage();
				}
			}
			if (IsHitLineSegment(*(*itr), 10.0f)) {
				_vPos = VAdd(_vPos, VScale(_oldPos, 0.4f));
			}
		}
	}
}

/**
 * �t���[�������F�v�Z
 */
void Player::Process(){

	// �L�[�̎擾
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ���[�h�Q�[���擾
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �����蔻��p�J�v�Z�����
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	// ���A�i���O�X�e�B�b�N���W
	float lx, ly;   
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �Q�[���p�b�h�uRT�v
	int rt = dinput.Z; 

	float analogMin = 0.3f;

	// �����O�̃X�e�[�^�X��ۑ�
	STATE oldState = _state;

	// �����O�̈ʒu��ۑ�
	_oldPos = _vPos;

	// �{�X�f�[�^�擾
	{
		VECTOR bsPos = Boss::GetInstance()->GetPos();
		float dx = _vPos.x - bsPos.x;
		float dz = _vPos.z - bsPos.z;
		float len = sqrt(dx * dx + dz * dz);
		_len = len;            //�f�o�b�O�p
		_bsAngle = atan2(dz, dx);
		if (len <= 50) {
			_nearPosFlag = true;
		}
		else {
			_nearPosFlag = false;
		}
	}

	// �J�����f�[�^�擾
	VECTOR camPos = Camera::GetInstance()->GetPos();      // �J�����ʒu
	VECTOR camTarg = Camera::GetInstance()->GetTarg();    // �J�����̒����_
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // �J�����̏��

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.0f,0.0f,0.0f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);


	// �Q�[���I�[�o�[����
	if (_gameOverFlag) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	// �q�b�g�|�C���g 0 �ŃQ�[���I�[�o�[
	if (_hitpoint <= 0) { 
		_gameOverFlag = true;
	}

	// �ړ�����
	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	// �}���`���b�N�V�X�e�����������Ă��Ȃ��Ƃ��͈ړ��\
	if (camState != Camera::STATE::MLS_LOCK && !_attackFlag) {
		// vec��rad����]������
		vec.x = cos(rad + camRad) * length;
		vec.z = sin(rad + camRad) * length;

		// vec�̕��ړ�
		_vPos = VAdd(_vPos, vec);

		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		if (VSize(vec) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
			if (camState == Camera::STATE::TARG_LOCK_ON){
				_vDir.x = -cos(_bsAngle);
                _vDir.z = -sin(_bsAngle);
				LeftAnalogDeg(length);
				
				if (!_isDash) {
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}
				if (_isCanJump) {
					_state = STATE::WALK;
				}
			}
		}
		else if (_isCanJump && !_shotFlag && !_attackFlag) {
			_state = STATE::WAIT;

		}

		// �d�͏���
		_vPos.y -= GRAVITY;
		if (_vPos.y < 0.0f) {
			_vPos.y = 0.0f;
		}
		
		// �W�����v
		JumpAction();
		
		// �Z�����_�b�V��
		float nowAngle = atan2(_vDir.z, _vDir.x);  // ���݂̃v���C���[�̐��ʊp�x
		VECTOR vDash{ 0.f,0.f,0.f };               // �_�b�V���������
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP) && _energy > CHARA_DATA->_egDash) {
			_mvSpd = CHARA_DATA->_mvSpdDash;
			_isShortDash = true;             // �Z�����_�b�V���ړ��X�^�[�g
			_isCanLongDash = true;           // �Z�����_�b�V������ �� �������_�b�V�������\�ƂȂ�
			_shortDashTime = SHORT_DASH_CNT;  // �Z�����_�b�V���ړ����Ԃ��Z�b�g
			
		}
		if (_isShortDash) {
			_shortDashTime--;
			if (_shortDashTime > 0) {
				_isDash = true;
				if (camState != Camera::STATE::TARG_LOCK_ON) {
					_state = STATE::FOR_DASH;
				}
				_isCharging = false;
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						LeftAnalogDeg(length);
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
					}
					else {
						vDash.x = cos(nowAngle) * _mvSpd;
						vDash.z = sin(nowAngle) * _mvSpd;
					}
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
			}
			else {
				_shortDashTime = 0;
				_isShortDash = false;
				_isDash = false;
			}
		}
		// �������_�b�V��
		if (key & PAD_INPUT_6) {		
			//�v���C���[���n��ɂ��� �A�������_�b�V���\(�Z�����_�b�V�����s������)�A�Z�����_�b�V���ړ����I����Ă���A�G�l���M�[0��肠��
			if (_isCanJump && _isCanLongDash && !_isShortDash && _energy > 0) {
				_isDash = true;
				_isCharging = false;
				if (camState != Camera::STATE::TARG_LOCK_ON) {
					_state = STATE::FOR_DASH;
				}
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						LeftAnalogDeg(length);
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
						_vPos.x += vDash.x;
						_vPos.z += vDash.z;
					}
					else {
						vDash.x = cos(nowAngle) * _mvSpd;
						vDash.z = sin(nowAngle) * _mvSpd;
						_vPos.x += vDash.x;
						_vPos.z += vDash.z;
					}
				}
			}
		}
		else {
			_isDash = false;
			_isCanLongDash = false;
		}

		// �G�l���M�[����
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)&& _energy < CHARA_DATA->_maxEnergy) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				if (!_isDash) {           // �_�b�V�����ĂȂ���Η��߉\
					_mvSpd = CHARA_DATA->_mvSpdChrg;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}


		// �ߐڍU��(����̂�)
		if (_vPos.y == 0.0f) {
			_attack->FirstAttack(this);
		}

        // �ˌ��U��
		ShotAttack(rt);
	}

    // �ߐڍU������(2���ڈȍ~)
	_attack->SecondAttack(this);

	if (_camStateMLS) {
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		_state = STATE::NONE;
	}
		

	// �}���`���b�N�V�X�e���p���`�N���ǉ�
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
	else {
		_camStateMLS = false;
	}

	// �G�l���M�[�Ǘ�
	EnergyManager(oldState);

	// �f�o�b�O�p
	if (trg & PAD_INPUT_7) {
		if (_swCharge) {
			_swCharge = false;
		}
		else {
			_swCharge = true;
		}
	}

	// �����蔻��
	Collision();

	// MLS�ɂ��e���Ԃ��ŃV�[���h�j�󂵂��ꍇ�A[�{�X�̒e�̐� * �w��̃G�l���M�[��]���񕜂���B
	if (Boss::GetInstance()->_mlsDownFlag) {
		_energy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	// ���f�����[�V�����ؑ�
	_motion->SwitchMotion(this, oldState);

	// �c��HP�ۑ�(�X�R�A�v�Z�p)
	gGlobal._remainingHP = _hitpoint;
}

/**
 * �t���[�������F�`��
 */
void Player::Render(){

    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.1f, 0.1f, 0.1f));
	{
		MV1SetPosition(_mh, _vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}

#if 1  // �f�o�b�O�p
	float angle = atan2(_vDir.z ,_vDir.x);
	float deg = angle * 180.f / DX_PI_F;
	int x = 100;
	int y = 140;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Player:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  deg    = %5.1f", deg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  spd    = %3.1f", _mvSpd); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  charge = %d", _isCharging); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dash   = %d", _isDash); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ��ST�p�x = %d", _lfAnalogDeg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP     = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  energy = %d, ON(1) / OFF(0) = %d (BACK�L�[�Őؑ�)", _energy, _swCharge); y += size;

	DrawFormatString(0, y, GetColor(255, 0, 0), "  �{�X�Ƃ̋��� = %4.2f", _len); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U���J�E���g = %d", _attackCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U����t���� = %d", _receptionTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U���۰�ގ��� = %d", _attackReloadTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�WHP = %d", _nowDmgHP); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�WSLD= %d", _nowDmgSld); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�W�ʏ� = %d", _nowDmgNorm); y += size;
	DrawString(0, y, "�@��ԁF",GetColor(255, 0, 0));
	switch (_state) {
	case STATE::WAIT:
		DrawString(x, y, "WAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(x, y, "WALK", GetColor(255, 0, 0)); break;
	case STATE::FOR_DASH:
		DrawString(x, y, "FOR DASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(x, y, "JUMP", GetColor(255, 0, 0)); break;
	case STATE::LEFT_MOVE:
		DrawString(x, y, "LEFT MOVE", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_MOVE:
		DrawString(x, y, "RIGHT MOVE", GetColor(255, 0, 0)); break;
	case STATE::BACK_MOVE:
		DrawString(x, y, "BACK MOVE", GetColor(255, 0, 0)); break;
	case STATE::LEFT_DASH:
		DrawString(x, y, "LEFT DASH", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_DASH:
		DrawString(x, y, "RIGHT DASH", GetColor(255, 0, 0)); break;
	case STATE::BACK_DASH:
		DrawString(x, y, "BACK DASH", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK1:
		DrawString(x, y, "WEAK ATTACK1", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK2:
		DrawString(x, y, "WEAK ATTACK2", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK3:
		DrawString(x, y, "WEAK ATTACK3", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK4:
		DrawString(x, y, "WEAK ATTACK4", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK1:
		DrawString(x, y, "STRG ATTACK1", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK2:
		DrawString(x, y, "STRG ATTACK2", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK3:
		DrawString(x, y, "STRG ATTACK3", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK4:
		DrawString(x, y, "STRG ATTACK4", GetColor(255, 0, 0)); break;
	case STATE::SHOT_ATCK:
		DrawString(x, y, "SHOT ATTACK", GetColor(255, 0, 0)); break;
	}

	DrawFormatString(0, 900, GetColor(255, 0, 0), "  ���e�� = %d / 100", _bulletNum); 
//	DrawCapsule3D(_capsulePos1, _capsulePos2, 1.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
//	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.5f, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
#endif
}