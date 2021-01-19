
#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"
#include "BulletServer.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "Reticle.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = ResourceServer::MV1LoadModel("res/model/���f�[�^/SDChar/SDChar.mv1");;

	Initialize();
}

Player::~Player()
{

}

void Player::Initialize()
{
	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = NOR_MV_SPD;
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
	_status.bulletNum = MAX_BULLET;
	_canShotFlag = true;
	_shotInterval = 5;
	_reloadTime = 90;
	_shotZeroFlag = false;

	//�G�l���M�[
	_status.energy = MAX_ENERGY;
	_atChargeFlag = true;
	_atChargeCnt = 30;

	//�q�b�g�|�C���g
	_status.hitpoint = MAX_HP;

	_gameOverCnt = 0;

	_camStateMLS = false;

	_swCharge = true;
}

void Player::JumpAction() 
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (_status.energy >= JUMP_ENERGY) {
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
			_mvSpd = NOR_MV_SPD;
			_jumpTime = 0.f;
		}
	}
	if (!_isCanJump) {
		float gravity = 0.9f;
		float inVel = 4.f;
		_vPos.y = inVel * _jumpTime - 0.5f * gravity * _jumpTime * _jumpTime;
	}
	
	_jumpTime += 0.2f;

	if (_vPos.y < GROUND_Y) {
		_vPos.y = GROUND_Y;
		if (_isCharging == false) {
			_isCanJump = true;
		}
	}
}

void Player::LeftAnalogDeg(float length)
{
	if (_isCanJump) {
		if (_isDash) {
			_mvSpd = DASH_MV_SPD;
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
			_mvSpd = NOR_MV_SPD;
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

void Player::EnergyManager(STATE oldState)
{
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	if (oldState != _state) { 
		// �W�����v(����)
		if (_state == STATE::JUMP) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
			_status.energy = _status.energy - JUMP_ENERGY;
		}
		// �Z�����_�b�V��(����)
		if (_isShortDash) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
			_status.energy = _status.energy - DASH_ENERGY;
		}
	}

	// �������_�b�V��(����)
	if(!_isShortDash && _isDash) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy--;
	}

	// �}���`���b�N�I���V�X�e��
	if (camState == Camera::STATE::MLS_LOCK) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy -= 12.5;
	}
	//�@����(��)
	if (_isCharging) {
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy += AT_CHARGE * 2.5;
	}


	// �����񕜊J�n�̃C���^�[�o��
	if (!_atChargeFlag) {
		_atChargeCnt--;
		if (_atChargeCnt <= 0){   // ���̎����񕜊J�n�Ԋu��݂���
			_atChargeCnt = 0;
			_atChargeFlag = true;
		}
	}
	// ������
	else if (!_isCharging){
		_status.energy += AT_CHARGE;
	}
}

void Player::Process()
{
	_oldPos = _vPos;

	// �L�[�̎擾
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �����蔻��p�J�v�Z�����
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 5.f, _vPos.z);

	// �J�X������p�J�v�Z�����
//	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
//	_capsulePos2 = VGet(_vPos.x, _vPos.y + 5.f, _vPos.z);

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // ���A�i���O�X�e�B�b�N�̍��W
	int rt = dinput.Z;    // �Q�[���p�b�h�uRT�v
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATE oldState = _state;

	// �J�����f�[�^�擾

	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// �{�X�f�[�^�擾
	VECTOR bsPos = Boss::GetInstance()->GetPos();
	{
		float dx = _vPos.x - bsPos.x;
		float dz = _vPos.z - bsPos.z;
		_bsAngle = atan2(dz, dx);
	}

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);

	/**
	* �Q�[���I�[�o�[����
	*/
	if (_gameOverCnt > 0) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}

	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::STATE::MLS_LOCK) {  // �}���`���b�N�V�X�e�����������Ă��Ȃ��Ƃ��͈ړ��\
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
					_mvSpd = NOR_MV_SPD;
				}
				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
					_mvSpd = NOR_MV_SPD;
				}
				if (_isCanJump) {
					_state = STATE::WALK;
				}
			}
		}
		else if (_isCanJump) {
			_state = STATE::WAIT;

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
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP) && _status.energy > DASH_ENERGY) {
			_mvSpd = DASH_MV_SPD;
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
			if (_isCanJump && _isCanLongDash && !_isShortDash && _status.energy > 0) {
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
		* �G�l���M�[�`���[�W
		*/
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				if (_state != STATE::FOR_DASH) {
					_mvSpd = CHARGE_MV_SPD;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}


		/**
		* �ˌ��U�� (�Q�[���p�b�hRT�Ŏˌ�)
		*/
		if (rt < -100 && !_isCharging && !_shotZeroFlag) { // ���ߏ�ԋy�ё��e�����[���ɂȂ����ꍇ�͎ˌ��s��
			if (_status.bulletNum == 0) {
				_shotZeroFlag = true;      // �e��ł��؂��Ă��܂��ƃt���O������(= true) �� �ˌ��s��
			}
			if (_status.bulletNum > 0) {
				if (_canShotFlag) {
					_reloadTime = 90;	   // �����[�h�J�n���Ԃ��Z�b�g
					_canShotFlag = false;
					_status.bulletNum--;
					ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
					PlayerBullet* bullet = new PlayerBullet();
					VECTOR tmp = _vPos;
					tmp.y = _vPos.y + 3.5;
					bullet->SetPos(tmp);
					modeGame->_objServer.Add(bullet);
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
			_reloadTime--;
			if (_shotZeroFlag) {            // �e��ł��؂����ꍇ�͑��������[�h�J�n
				if (_status.bulletNum < MAX_BULLET) {
					_status.bulletNum++;
				}
			}
			else if (_reloadTime <= 0) {    // �e���c���Ă����Ԃ������[�h�J�n���ԃ[���Ń����[�h�J�n
				if (_status.bulletNum < MAX_BULLET) {
					_status.bulletNum++;
				}
			}

		}
		if (_status.bulletNum == MAX_BULLET) {
			_shotZeroFlag = false;          // �����[�h������_shotZeroFlag����(= false)
		}
	}

/*	if (camState == Camera::STATE::MLS_LOCK) {
		_camStateMLS = true;
	}*/
	
		
	// �}���`���b�N�V�X�e���p���`�N���ǉ�	
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = new Reticle();
		modeGame->_objServer.Add(reticle);
	}



	/**
	* �G�l���M�[�Ǘ�
	*/
	if (_status.energy > 0 || _status.energy < MAX_ENERGY) {
		if (_swCharge) {               // �f�o�b�O�p
			EnergyManager(oldState);
		}
	}
	if (_status.energy < 0) {
		_status.energy = 0;
	}
	if (_status.energy > MAX_ENERGY) {
		_status.energy = MAX_ENERGY;
	}

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
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {  // �X�e�[�W
				if (IsHitStage(*(*itr), 2.0f) == true) {
					VECTOR slideVec;
					slideVec = VCross(vec, (*itr)->_hitPolyDim.Dim->Normal);
					slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
					_vPos = VAdd(_oldPos, slideVec);
					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.03f));
				}
			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) { // �{�X�̒e
				// ���e
				if (IsHitLineSegment(*(*itr), 1.0f)) {
					modeGame->_objServer.Del(*itr);
					_status.hitpoint -= 100;
					if (_status.hitpoint <= 0) {
						_gameOverCnt = 60;
					}
				}
				// �J�X������
				if (IsHitLineSegment(*(*itr), 2.5f)) {
					_status.energy += 3;				
				}		
			}
		}
	}



	if (oldState == _state) {
		_playTime += 0.5f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "idle"), -1, FALSE);
			break;
		case STATE::WALK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
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
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);
	
		_playTime = 0.0f;
	}

	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}



}

void Player::Render()
{
    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.05f, 0.05f, 0.05f));
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
	float angle = atan2(_vDir.x * -1, _vDir.z * -1);
	float deg = angle * 180.f / DX_PI_F;
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
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP     = %d", _status.hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  energy = %d, ON(1) / OFF(0) = %d (BACK�L�[�Őؑ�)", _status.energy, _swCharge); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ���e�� = %d", _status.bulletNum); y += size;
	switch (_state) {
	case STATE::WAIT:
		DrawString(0, y, "�@��ԁFWAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(0, y, "�@��ԁFWALK", GetColor(255, 0, 0)); break;
	case STATE::FOR_DASH:
		DrawString(0, y, "�@��ԁFFOR DASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(0, y, "�@��ԁFJUMP", GetColor(255, 0, 0)); break;
	case STATE::LEFT_MOVE:
		DrawString(0, y, "�@��ԁFLEFT MOVE", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_MOVE:
		DrawString(0, y, "�@��ԁFRIGHT MOVE", GetColor(255, 0, 0)); break;
	case STATE::BACK_MOVE:
		DrawString(0, y, "�@��ԁFBACK MOVE", GetColor(255, 0, 0)); break;
	case STATE::LEFT_DASH:
		DrawString(0, y, "�@��ԁFLEFT DASH", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_DASH:
		DrawString(0, y, "�@��ԁFRIGHT DASH", GetColor(255, 0, 0)); break;
	case STATE::BACK_DASH:
		DrawString(0, y, "�@��ԁFBACK DASH", GetColor(255, 0, 0)); break;
	}
	DrawCapsule3D(_capsulePos1, _capsulePos2, 1.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.5f, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
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