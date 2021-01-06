
#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = MV1LoadModel("res/model/���f�[�^/SDChar/SDChar.mv1");
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
	_mvSpd = 0.8f;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.f;
	_jumpTime = 0.f;
	//_state = STATE::WAIT;
	_inVel = 0.f;
	_isCanJump = true;
	_isCharging = false;
	_hit = false;

	//_blt.shotflg = false;
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
	float lx, ly;           // ���E�A�i���O�X�e�B�b�N�̍��W
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATE oldState = _state;

	// �J�����f�[�^�擾
	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	if (length < analogMin) {
		// ���͂������������瓮���Ȃ��������Ƃɂ���
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::GetInstance()->STATE::MLS_LOCK) {
		// vec��rad����]������
		vec.x = cos(rad + camRad) * length;
		vec.z = sin(rad + camRad) * length;

		// vec�̕��ړ�
		_vPos = VAdd(_vPos, vec);

#if 0
		if (VSize(vec) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
			_vDir = vec;
			_state = STATE::WALK;
			
		}
		switch (_state) {
		case STATE::WAIT:
			if (VSize(vec) > 0.f) {
				_state = STATE::WALK;
			}
			if (key & PAD_INPUT_3) {
				_state = STATE::CHARGE;
			}
			if (trg & PAD_INPUT_1 && _isCanJump) {
				_state = STATE::JUMP;
				_vel = 1.2f;
			}
			if (trg & PAD_INPUT_6) {
				_state = STATE::DASH;
			}
			break;
		case STATE::WALK:
			if (VSize(vec) == 0.f) {
				_state = STATE::WAIT;
			}
			break;
		case STATE::DASH:
			if (key & PAD_INPUT_6) {
				_mvSpd = 1.2f;
			}
			else {
				_state = STATE::WALK;
			}
			break;
		case STATE::JUMP:
			
			break;
		case STATE::CHARGE:
			_mvSpd = 0.4f;
			if (!(key & PAD_INPUT_3)) {
				_state = STATE::WAIT;
			}
			break;
		default:
			_state = STATE::WAIT;
			_mvSpd = 0.8f;
		}
#else
		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		if (VSize(vec) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
			_vDir = vec;
			_mvSpd = 0.8f;
		//	if (_vPos.y == GROUND_Y) {
			if (_isCanJump) {
				_state = STATE::WALK;
			}
		}
		//else if(_vPos.y == GROUND_Y){
		else if (_isCanJump) {
			_state = STATE::WAIT;
		}

		// �W�����v ///////////////////////////////////////////////////
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
			_mvSpd = 0.8f;
			_inVel = 1.2f;      // �W�����v1
			_jumpTime = 0.f;    // �W�����v2
		}

		// ���� //////////////////////////////////////////////////////
		if (key & PAD_INPUT_3) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				_mvSpd = 0.4f;
				_isCharging = true;
			}
		}
		else {
			_isCharging = false;
		}
		// �_�b�V�� ///////////////////////////////////////////////////
		if (key & PAD_INPUT_6) {
			
			if (_isCanJump) {
				_mvSpd = 1.2f;
				_state = STATE::DASH;
				_isCharging = false;    // �_�b�V�����͗��ߕs��
			}
		}
		//	if (trg & PAD_INPUT_6) {
		//		_vPos = VAdd(_vPos, VScale(_vDir, 20.f));
		//	}
#endif

#if 0
		// �W�����v1
		float acc = 0.05f;
		_inVel -= acc;
		_vPos.y += _inVel;
		
#else
		// �W�����v2
		if (!_isCanJump) {
			float gravity = 0.9f;
			float inVel = 4.f;
			_vPos.y = inVel * _jumpTime - 0.5 * gravity * _jumpTime * _jumpTime;
		}
		_jumpTime += 0.2f;
#endif

		if (_vPos.y < GROUND_Y) {
			_vPos.y = GROUND_Y;
			_inVel = 0.f;
			if (_isCharging == false) {
				_isCanJump = true;
			}
		}
		
	}


	// �ǂƂ̓����蔻��A�ǂ��� //////////////////////////////////////////////////
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
	_hitPolyDim = MV1CollCheck_Capsule(_mhMap, -1, _capsulePos1, _capsulePos2, 2.f);
	
	if (_hitPolyDim.HitNum >= 1) {
		
		VECTOR slideVec;
		slideVec = VCross(vec, _hitPolyDim.Dim->Normal);
		slideVec = VCross(_hitPolyDim.Dim->Normal, slideVec);
		_vPos = VAdd(_oldPos, slideVec);
		_vPos = VAdd(_vPos, VScale(_hitPolyDim.Dim->Normal, 0.03f));
	
		_hit = true;
	}
	else {
		_hit = false;
	}
	
	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldState == _state) {
		_playTime += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "idle"), -1, FALSE);
			break;
		case STATE::WALK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
			break;
		case STATE::JUMP:
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
	if (_hit) {
		DrawString(0, 400, "�ǂɓ�����", GetColor(255, 0, 0), GetColor(255, 0, 0));
	}
	float angle = atan2(_vDir.x * -1, _vDir.z * -1);
	float deg = angle * 180.f / DX_PI_F;
	int y = 100;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Player:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  deg    = %5.1f", deg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  spd    = %3.1f", _mvSpd); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ����    = %d", _isCharging); y += size;
	switch (_state) {
	case STATE::WAIT:
		DrawString(0, y, "�@��ԁFWAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(0, y, "�@��ԁFWALK", GetColor(255, 0, 0)); break;
	case STATE::DASH:
		DrawString(0, y, "�@��ԁFDASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(0, y, "�@��ԁFJUMP", GetColor(255, 0, 0)); break;
	case STATE::CHARGE:
		DrawString(0, y, "�@��ԁFCHARGE", GetColor(255, 0, 0)); break;
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