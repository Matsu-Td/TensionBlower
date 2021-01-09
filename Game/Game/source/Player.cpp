
#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = ResourceServer::MV1LoadModel("res/model/���f�[�^/SDChar/SDChar.mv1");;
	_mhMap = MV1LoadModel("res/model/���f�[�^/stage_dummy02.mv1");

	MV1SetupCollInfo(_mhMap, -1, 16, 16, 16);
	Initialize();
}

Player::~Player()
{

}

void Player::Initialize()
{
	_vPos = VGet(0.f, 0.f, -115.f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = NOR_MV_SPD;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.f;
	_jumpTime = 0.f;
	_isCanJump = true;
	_isCharging = false;
	_isShortDash = false;
}

void Player::JumpAction() 
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
		_state = STATE::JUMP;
		_isCanJump = false;
		_mvSpd = NOR_MV_SPD;
		_jumpTime = 0.f;
	}
	if (!_isCanJump) {
		float gravity = 0.9f;
		float inVel = 4.f;
		_vPos.y = inVel * _jumpTime - 0.5 * gravity * _jumpTime * _jumpTime;
	}
	_jumpTime += 0.2f;

	if (_vPos.y < GROUND_Y) {
		_vPos.y = GROUND_Y;
		if (_isCharging == false) {
			_isCanJump = true;
		}
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
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 4.f, _vPos.z);

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // ���A�i���O�X�e�B�b�N�̍��W
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
	//	_vDir.x = -cos(_bsAngle);
	//	_vDir.z = -sin(_bsAngle);
	}

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = rad * 180.0f / DX_PI_F;
	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::GetInstance()->STATE::MLS_LOCK) {  // �}���`���b�N�V�X�e�����������Ă��Ȃ��Ƃ��͈ړ��\
		// vec��rad����]������
		vec.x = cos(rad + camRad) * length;
		vec.z = sin(rad + camRad) * length;

		// vec�̕��ړ�
		_vPos = VAdd(_vPos, vec);

		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		if (VSize(vec) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
			_vDir = vec;
			if (_state != STATE::DASH) {
				_mvSpd = NOR_MV_SPD;
			}
			if (_isCanJump) {
				_state = STATE::WALK;
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
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP)) {
			_mvSpd = DASH_MV_SPD;
			_isShortDash = true;
			_dashCnt = 10;
		}
		if (_isShortDash) {
			_dashCnt--;
			if (_dashCnt > 0) {
				_state = STATE::DASH;
				_isCharging = false;
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
						_vDir.x = -cos(_bsAngle);
						_vDir.z = -sin(_bsAngle);
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
				_dashCnt = 0;
				_isShortDash = false;
			}
		}
		/**
		* �������_�b�V��
		*/
		if (key & PAD_INPUT_6) {		
			if (_isCanJump && !_isShortDash) {
				_state = STATE::DASH;
				_isCharging = false;
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
						_vPos.x += vDash.x;
						_vPos.z += vDash.z;
						_vDir.x = -cos(_bsAngle);
						_vDir.z = -sin(_bsAngle);
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
		/**
		* �G�l���M�[����
		*/
		if (key & PAD_INPUT_3) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				if (_state != STATE::DASH) {
					_mvSpd = CHARGE_MV_SPD;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}
	}
	/**
	* �ǂƂ̓����蔻��A�ǂ���
	*/
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
	_hitPolyDim = MV1CollCheck_Capsule(_mhMap, -1, _capsulePos1, _capsulePos2, 2.f);
	
	if (_hitPolyDim.HitNum >= 1) {	
		VECTOR slideVec;
		slideVec = VCross(vec, _hitPolyDim.Dim->Normal);
		slideVec = VCross(_hitPolyDim.Dim->Normal, slideVec);
		_vPos = VAdd(_oldPos, slideVec);
		_vPos = VAdd(_vPos, VScale(_hitPolyDim.Dim->Normal, 0.03f));
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
		case STATE::L_SIDE_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::R_SIDE_DASH:
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

	MV1CollResultPolyDimTerminate(_hitPolyDim);

	// �ˌ�
	_bullet.Process();
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
	// �ˌ�
	_bullet.Render();

#if 1
	float angle = atan2(_vDir.x * -1, _vDir.z * -1);
	float deg = angle * 180.f / DX_PI_F;
	int y = 125;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Player:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  deg    = %5.1f", deg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  spd    = %3.1f", _mvSpd); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  charge = %d", _isCharging); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ��ST�p�x = %f", _lfAnalogDeg); y += size;
	switch (_state) {
	case STATE::WAIT:
		DrawString(0, y, "�@��ԁFWAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(0, y, "�@��ԁFWALK", GetColor(255, 0, 0)); break;
	case STATE::DASH:
		DrawString(0, y, "�@��ԁFDASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(0, y, "�@��ԁFJUMP", GetColor(255, 0, 0)); break;
	case STATE::L_SIDE_DASH:
		DrawString(0, y, "�@��ԁFLEFT", GetColor(255, 0, 0)); break;
	case STATE::R_SIDE_DASH:
		DrawString(0, y, "�@��ԁFRIGHT", GetColor(255, 0, 0)); break;
	case STATE::BACK_DASH:
		DrawString(0, y, "�@��ԁFBACK", GetColor(255, 0, 0)); break;
	}
	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
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