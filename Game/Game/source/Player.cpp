
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
}


Player::~Player(){
}


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
	//�ˌ�
	_bulletNum = MAX_BULLET;
	_canShotFlag = true;
	_shotInterval = 5;
	_reloadTime = RELOAD_TIME;
	_shotZeroFlag = false;

	//�G�l���M�[
	_energy = CHARA_DATA->_maxEnergy;
	_atChargeFlag = true;
	_atChargeCnt = 30;

	//�q�b�g�|�C���g
	_hitpoint = CHARA_DATA->_maxHP;

	_gameOverCnt = 60;
	_gameOverFlag = false;

	_camStateMLS = false;

	_swCharge = true;

	_shotFlag = false;

	_attackFlag = false;
	_receptionTime = 0;
	_attackReloadTime = 0;
	_hitFlag = false;
	_canHitFlag = false;

	_attackCnt = 0;

	_attackTotalTime["weak_atck1"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck2"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck3"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck4"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck1"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck2"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck3"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck4"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
}


void Player::JumpAction() {

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_energy >= CHARA_DATA->_egJump) {
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
//			_mvSpd = NOR_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdNorm;
			_jumpTime = 0.f;
		}
	}
	if (!_isCanJump) {
		//float gravity = GRAVITY;
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
/*
MATRIX Player::MV1GetFrameRotateMatrix(int MHandle, int FrameIndex, double Xaxis, double Yaxis, double Zaxis, double modelScale) {
	//�e�t���[���̎擾
	int ParentFrame = MV1GetFrameParent(MHandle, FrameIndex);

	//�e�t���[�������݂���(=���Ȃ킿ParentFrame��-2�ł͂Ȃ�)�Ȃ�Α��΍��W���������s�ړ�����s����擾
	//�e�t���[�������݂��Ȃ��Ȃ�ΒP�ʍs��𓾂�(=���Ȃ킿���s�ړ����Ȃ�)   
	MATRIX MTranslate;
	if (-2 != ParentFrame)
	{
		//�e�q�t���[���̍��W�̎擾
		VECTOR vecParent = MV1GetFramePosition(MHandle, ParentFrame);
		VECTOR vecChild = MV1GetFramePosition(MHandle, FrameIndex);

		//�e����ɂ����q�̑��΍��W���擾
		VECTOR vecRerativPar2Chi = VSub(vecChild, vecParent);

		//���f�������{�ɑ傫���Ȃ��Ă��邩�ɏ]���đ��΍��W��␳
		if (0 != modelScale)
		{
			modelScale = 1 / modelScale;
		}
		vecRerativPar2Chi = VScale(vecRerativPar2Chi, modelScale);
		MTranslate = MGetTranslate(vecRerativPar2Chi);
	}
	else
	{
		MTranslate = MGetIdent();
	}

	//���ꂼ��̎��ɉ����ĉ�]����s����擾
	MATRIX MXaxis = MGetRotX(Xaxis);
	MATRIX MYaxis = MGetRotY(Yaxis);
	MATRIX MZaxis = MGetRotZ(Zaxis);

	//�����ɉ�]�����Ă��畽�s�ړ������s����

	MATRIX MReturn = MMult(MMult(MMult(MXaxis, MYaxis), MZaxis), MTranslate);

	return MReturn;
}
*/

void Player::LeftAnalogDeg(float length){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_isCanJump) {
		if (_isDash) {
//			_mvSpd = DASH_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdDash;
			if (_lfAnalogDeg >= 120 || _lfAnalogDeg <= -120) {
				_state = STATE::FOR_DASH;
			}
			else if (_lfAnalogDeg < -45 && _lfAnalogDeg > -120) {
				_state = STATE::LEFT_DASH;
			}
			else if (_lfAnalogDeg > 45 && _lfAnalogDeg < 120) {
				_state = STATE::RIGHT_DASH;
			}
			else if (_lfAnalogDeg >= -45 && _lfAnalogDeg <= 45 && length >= 0.3f) {
				_state = STATE::BACK_DASH;
			}
			else {
				_state = STATE::FOR_DASH;  // ���͂�RB�̂�
			}
		}
		else {
//			_mvSpd = NOR_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdNorm;
			if (_lfAnalogDeg >= 120 || _lfAnalogDeg <= -120) {
				_state = STATE::WALK;
			}
			else if (_lfAnalogDeg < -45 && _lfAnalogDeg > -120) {
				_state = STATE::LEFT_MOVE;
			}
			else if (_lfAnalogDeg > 45 && _lfAnalogDeg < 120) {
				_state = STATE::RIGHT_MOVE;
			}
			else if (_lfAnalogDeg >= -45 && _lfAnalogDeg <= 45) {
				_state = STATE::BACK_MOVE;
			}
		}
	}
}

void Player::SetAttackDamage(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	switch (_state) {
	case STATE::WEAK_ATCK1:
		_nowDmgHP = CHARA_DATA->_wkDmgHP1;
		_nowDmgSld = CHARA_DATA->_wkDmgSld1;
		_nowDmgNorm = CHARA_DATA->_wkDmg1;
		break;
	case STATE::WEAK_ATCK2:
		_nowDmgHP = CHARA_DATA->_wkDmgHP2;
		_nowDmgSld = CHARA_DATA->_wkDmgSld2;
		_nowDmgNorm = CHARA_DATA->_wkDmg2;
		break;
	case STATE::WEAK_ATCK3:
		_nowDmgHP = CHARA_DATA->_wkDmgHP3;
		_nowDmgSld = CHARA_DATA->_wkDmgSld3;
		_nowDmgNorm = CHARA_DATA->_wkDmg3;
		break;
	case STATE::WEAK_ATCK4:
		_nowDmgHP = CHARA_DATA->_wkDmgHP4;
		_nowDmgSld = CHARA_DATA->_wkDmgSld4;
		_nowDmgNorm = CHARA_DATA->_wkDmg4;
		break;
	case STATE::STRG_ATCK1:
		_nowDmgHP = CHARA_DATA->_stDmgHP1;
		_nowDmgSld = CHARA_DATA->_stDmgSld1;
		_nowDmgNorm = CHARA_DATA->_stDmg1;
		break;
	case STATE::STRG_ATCK2:
		_nowDmgHP = CHARA_DATA->_stDmgHP2;
		_nowDmgSld = CHARA_DATA->_stDmgSld2;
		_nowDmgNorm = CHARA_DATA->_stDmg2;
		break;
	case STATE::STRG_ATCK3:
		_nowDmgHP = CHARA_DATA->_stDmgHP3;
		_nowDmgSld = CHARA_DATA->_stDmgSld3;
		_nowDmgNorm = CHARA_DATA->_stDmg3;
		break;
	case STATE::STRG_ATCK4:
		_nowDmgHP = CHARA_DATA->_stDmgHP4;
		_nowDmgSld = CHARA_DATA->_stDmgSld4;
		_nowDmgNorm = CHARA_DATA->_stDmg4;
		break;
	}
}

void Player::AttackAction() {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	// �U���J�E���g
	if (_attackCnt <= 0) {
		_attackCnt = 0;
		_hitFlag = false;
	}
	else {
		_attackCnt--;
	}

	// ��t����
	if (_attackCnt <= 20) {
		_receptionTime--;
	}
	if (_receptionTime <= 0) {
		_receptionTime = 0;
		_attackReloadTime = RELOAD_TIME;
		_attackFlag = false;
	}

	if (!_hitFlag) {
		if (_attackCnt >= 20 && _attackCnt < 35) {
			_canHitFlag = true;
		}
		else {
			_canHitFlag = false;
		}
	}

	switch (_state) {
	case STATE::WEAK_ATCK1:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��2�֔h��
			if (trg & PAD_INPUT_4) {                  
				if (_energy < CHARA_DATA->_egAtck2) { // �G�l���M�[�c�ʃ`�F�b�N
					return;
				}
				_state = STATE::STRG_ATCK2;
//				_status.energy -= CHARA_DATA->_egAtck2;  // �G�l���M�[����
				_atChargeFlag = false;                   // �U�����G�l���M�[���ߕs��
				_atChargeCnt = AT_CHARGE_CNT;            // ���ߕ��A���ԃZ�b�g
				_attackCnt = _attackTotalTime["strg_atck2"];
				_receptionTime = RECEPTION_TIME;                     // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
			// ��ߐڍU��2�֔h��
			else if (trg & PAD_INPUT_B) {             
				_state = STATE::WEAK_ATCK2;
				_attackCnt = _attackTotalTime["weak_atck2"];
				_receptionTime = RECEPTION_TIME;                     // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
		}
		
		break;
	case STATE::WEAK_ATCK2:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��3�֔h��
			if (trg & PAD_INPUT_4) {                   
				if (_energy < CHARA_DATA->_egAtck3) { // �G�l���M�[�c�ʃ`�F�b�N
					return;
				}
				_state = STATE::STRG_ATCK3;
//				_status.energy -= CHARA_DATA->_egAtck3;  // �G�l���M�[����
				_atChargeFlag = false;                   // �U�����G�l���M�[���ߕs��
				_atChargeCnt = AT_CHARGE_CNT;            // ���ߕ��A���ԃZ�b�g
				_attackCnt = _attackTotalTime["strg_atck3"];
				_receptionTime = RECEPTION_TIME;         // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
			// ��ߐڍU��3�֔h��
			else if (trg & PAD_INPUT_B) {              
				_state = STATE::WEAK_ATCK3;
				_attackCnt = _attackTotalTime["weak_atck3"];
				_receptionTime = RECEPTION_TIME;         // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
		}
		break;
	case STATE::WEAK_ATCK3:
		if (_receptionTime < RECEPTION_TIME) {
			// ���ߐڍU��4�֔h��
			if (trg & PAD_INPUT_4) {                   
				if (_energy < CHARA_DATA->_egAtck4) { // �G�l���M�[�c�ʃ`�F�b�N
					return;
				}
				_state = STATE::STRG_ATCK4;
//				_status.energy -= CHARA_DATA->_egAtck4;  // �G�l���M�[����
				_atChargeFlag = false;                   // �U�����G�l���M�[���ߕs��
				_atChargeCnt = AT_CHARGE_CNT;            // ���ߕ��A���ԃZ�b�g
			    _attackCnt = _attackTotalTime["strg_atck4"];
				_receptionTime = RECEPTION_TIME;         // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
			// ��ߐڍU��4�֔h��
			else if (trg & PAD_INPUT_B) {              
				_state = STATE::WEAK_ATCK4;
				_attackCnt = _attackTotalTime["weak_atck4"];
				_receptionTime = RECEPTION_TIME;         // ���U����t���ԃZ�b�g
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
			}
		}
		break;
		// �U���h���I���i��U��4,���U��1�`4�j
	case STATE::WEAK_ATCK4:     
		if (_attackCnt <= 0) {
			_attackFlag = false;               // �ߐڍU���I��
			_attackReloadTime = RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	case STATE::STRG_ATCK1:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // �ߐڍU���I��
			_attackReloadTime = RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	case STATE::STRG_ATCK2:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // �ߐڍU���I��
			_attackReloadTime = RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	case STATE::STRG_ATCK3:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // �ߐڍU���I��
			_attackReloadTime = RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	case STATE::STRG_ATCK4:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // �ߐڍU���I��
			_attackReloadTime = RELOAD_TIME;   // �ߐڍU�������[�h���ԃZ�b�g
		}
		break;
	}
}


void Player::EnergyManager(STATE oldState){

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float addEne;

	if (_energy > CHARA_DATA->_maxEnergy) {  // �G�l���M�[�񕜎��ɍő�G�l���M�[�l�𒴂���̂�h��
		_energy = CHARA_DATA->_maxEnergy;

	}

	if (oldState != _state) { 
		// �W�����v(����)
		if (_state == STATE::JUMP) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
//			_energy -= JUMP_ENERGY;
			_energy -= CHARA_DATA->_egJump;
		}
		// �Z�����_�b�V��(����)
		if (_isShortDash) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
//			_energy -=  DASH_ENERGY;
			_energy -= CHARA_DATA->_egDash;
		}
	}

	// �������_�b�V��(����)
	if(!_isShortDash && _isDash) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_energy--;
	}

	// �}���`���b�N�I���V�X�e��(����)
	if (camState == Camera::STATE::MLS_LOCK) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
//		_energy -= 12.5;
		_energy -= CHARA_DATA->_egMLS;
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
//		_atChargeCnt = AT_CHARGE_CNT;
//		_energy += AT_CHARGE * 2.5 * addEne;
		_energy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
		gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
	}

	// �����񕜊J�n�̃C���^�[�o��
	if (!_atChargeFlag) {
		_atChargeCnt--;
		if (_atChargeCnt <= 0){   // ���̎����񕜊J�n�Ԋu��݂���
			_atChargeCnt = 0;
			_atChargeFlag = true;
		}
	}
	// ������(��)
	else if (!_isCharging){
//		_status.energy += AT_CHARGE * addEne;
		_energy += CHARA_DATA->_egAutoRec * addEne;
		gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * addEne;
	}
}

void Player::Process(){

	// �L�[�̎擾
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �����蔻��p�J�v�Z�����
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // ���A�i���O�X�e�B�b�N�̍��W
	int rt = dinput.Z;    // �Q�[���p�b�h�uRT�v
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

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
	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// ���[�h�Q�[���擾
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));


	// �ړ����������߂�
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);


	/**
	* �Q�[���I�[�o�[����
	*/
	if (_gameOverFlag) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	if (_hitpoint <= 0) {   // �q�b�g�|�C���g 0 �ŃQ�[���I�[�o�[
		_gameOverFlag = true;
	}


	/**
	* �ړ�����
	*/
	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::STATE::MLS_LOCK && !_attackFlag) {  // �}���`���b�N�V�X�e�����������Ă��Ȃ��Ƃ��͈ړ��\
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
//					_mvSpd = NOR_MV_SPD;
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
//					_mvSpd = NOR_MV_SPD;
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

		/**
        * �d�͏���
        */
		_vPos.y -= GRAVITY;
		if (_vPos.y < 0.0f) {
			_vPos.y = 0.0f;
		}
		
		/**
		* �W�����v
		*/
		JumpAction();
		


		/**
        * �Z�����_�b�V��
        */
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
		/**
		* �������_�b�V��
		*/
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

		/**
		* �G�l���M�[����
		*/
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)&& _energy < CHARA_DATA->_maxEnergy) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				if (!_isDash) {           // �_�b�V�����ĂȂ���Η��߉\
//					_mvSpd = CHARGE_MV_SPD;
					_mvSpd = CHARA_DATA->_mvSpdChrg;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}

		/**
		* �ߐڍU������(����̂�)
		*/
		if (_vPos.y == 0.0f && _attackReloadTime == 0) {
			if (trg & PAD_INPUT_B && !_attackFlag) {
				_state = STATE::WEAK_ATCK1;
				_attackFlag = true;
				_attackCnt = _attackTotalTime["weak_atck1"];
				_receptionTime = RECEPTION_TIME;
				_hitFlag = false;
				SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g

			}
			if (trg & PAD_INPUT_4 && !_attackFlag) {
				if (_energy >= CHARA_DATA->_egAtck1) {  // �G�l���M�[�c�ʃ`�F�b�N
					_state = STATE::STRG_ATCK1;
					_energy -= CHARA_DATA->_egAtck1;    // �G�l���M�[����
					_atChargeFlag = false;                     // �U�����G�l���M�[���ߕs�� 
					_atChargeCnt = AT_CHARGE_CNT;              // ���ߕ��A���ԃZ�b�g
					_attackFlag = true;
					_attackCnt = _attackTotalTime["strg_atck1"];
					_receptionTime = RECEPTION_TIME;
					_hitFlag = false;
					SetAttackDamage();   // ���݂̋ߐڍU���̃{�X�ւ̃_���[�W�ʂ��Z�b�g
				}
			}
		}
		

		/**
		* �ˌ��U�� (�Q�[���p�b�hRT�Ŏˌ�)
		*/
		int rtMin = -100;
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
//					ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
					PlayerBullet* bullet = new PlayerBullet();
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
    * �ߐڍU������(2���ڈȍ~)
    */
	if (_attackFlag) {
		AttackAction();
	}
	if (_attackReloadTime > 0) {
		_attackReloadTime--;
	}

	if (_camStateMLS) {
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		_state = STATE::NONE;
	}
		

	/**
	*  �}���`���b�N�V�X�e���p���`�N���ǉ�
	*/
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
//		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = new Reticle();
		modeGame->_objServer.Add(reticle);
	}
	else {
		_camStateMLS = false;
	}



	/**
	* �G�l���M�[�Ǘ�
	*/
	if (_energy > 0 || _energy < CHARA_DATA->_maxEnergy) {
		if (_swCharge) {               // �f�o�b�O�p
			EnergyManager(oldState);
		}
	}
	if (_energy < 0) {
		_energy = 0;
	}
	if (_energy > CHARA_DATA->_maxEnergy) {
		_energy = CHARA_DATA->_maxEnergy;
	}

	// �f�o�b�O�p
	if (trg & PAD_INPUT_7) {
		if (_swCharge) {
			_swCharge = false;
		}
		else {
			_swCharge = true;
		}
	}


	/**
	* �����蔻��
	*/
	{
//		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {  // �X�e�[�W
				if (IsHitStage(*(*itr), 2.0f) == true) {
					VECTOR slideVec;
					slideVec = VCross(_vDir, (*itr)->_hitPolyDim.Dim->Normal);
					slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
					_vPos = VAdd(_oldPos, slideVec);
					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.5f));
					//					_vPos = VAdd(_vPos, (*itr)->_hitPolyDim.Dim->Normal);
				}
				

			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) { // �{�X�̒e
				// ���e
				if (IsHitLineSegment(*(*itr), 1.5f)) {
					modeGame->_objServer.Del(*itr);
					_hitpoint -= CHARA_DATA->_boss.shotDmg;
				}
				// �J�X������(�G�l���M�[��)
				if (IsHitLineSegment(*(*itr), 2.5f)) {
//					_status.energy += 3;
					_energy += CHARA_DATA->_egAvoid;
					gGlobal._totalGetEnergy += CHARA_DATA->_egAvoid;
				}
				if (Boss::GetInstance()->_mlsDownFlag) {
					modeGame->_objServer.Del(*itr);
					
				}
			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) { // �{�X
				if (IsHitArc_Sphere(*(*itr))==true) {
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
	// MLS�ɂ��e���Ԃ��ŃV�[���h�j�󂵂��ꍇ�A[�{�X�̒e�̐� * �w��̃G�l���M�[��]���񕜂���B
	if (Boss::GetInstance()->_mlsDownFlag) {
		_energy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	/**
	* ���[�V�����ؑ�
	*/
	if (oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
//			MV1ResetFrameUserLocalMatrix(_mh, 94);
		}
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "waitmove"), -1, FALSE);
			break;
		case STATE::WALK:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
			break;
		case STATE::JUMP:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::FOR_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::LEFT_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::RIGHT_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::BACK_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::LEFT_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::RIGHT_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::BACK_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::WEAK_ATCK1:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);

			break;
		case STATE::WEAK_ATCK2:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::WEAK_ATCK3:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::WEAK_ATCK4:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK1:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK2:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK3:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK4:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::SHOT_ATCK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "shoot"), -1, FALSE);
//			MATRIX Mrotate = MV1GetFrameRotateMatrix(_mh, 94, 0, 0.2 * 2 * DX_PI_F, 0, 0.1);
//			MV1SetFrameUserLocalMatrix(_mh, 94, Mrotate);
			break;
		}

		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}

	if (!_attackFlag) {
		if (_playTime >= _totalTime) {
			_playTime = 0.0f;
		}
	}

	// �c��HP�ۑ�(�X�R�A�v�Z�p)
	gGlobal._remainingHP = _hitpoint;
}

void Player::Render(){
    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.1f, 0.1f, 0.1f));
	{
		MV1SetPosition(_mh, _vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}

#if 1
//	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
//	VECTOR pl = modeGame->_pl->GetPos();
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

/* ���t�@�C������̕ϐ��l�������Ă�����@��
//VECTOR _cam = Camera::GetInstance()-GetPos();
	//ModeGame* modegame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	//printfDx("%f\n", _cam);

		// �V���O���g��������
	VECTOR camPos = Camera::GetInstance()->GetPos();
	DrawFormatString(0, 100, GetColor(255, 0, 0), "  camPos.x = %5.2f", camPos.x);
	DrawFormatString(0, 120, GetColor(255, 0, 0), "  camPos.y = %5.2f", camPos.y);
	DrawFormatString(0, 140, GetColor(255, 0, 0), "  camPos.z = %5.2f", camPos.z);
*/

//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
/*	_hitPolyDim = MV1CollCheck_Capsule(_mhMap, -1, _capsulePos1, _capsulePos2, 2.f);

	if (_hitPolyDim.HitNum >= 1) {
		VECTOR slideVec;
		slideVec = VCross(vec, _hitPolyDim.Dim->Normal);
		slideVec = VCross(_hitPolyDim.Dim->Normal, slideVec);
		_vPos = VAdd(_oldPos, slideVec);
		_vPos = VAdd(_vPos, VScale(_hitPolyDim.Dim->Normal, 0.03f));
	}*/