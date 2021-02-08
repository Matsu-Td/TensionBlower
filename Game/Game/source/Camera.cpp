
/**
 * @file  Camera.cpp
 * @brief �J�����֘A����
 *
 * @date 2021-02-08
 */

#include "Camera.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "Boss.h"

Camera* Camera::_pInstance = NULL;

Camera::Camera(){
	_pInstance = this;
//	_reticle.cg = ResourceServer::LoadGraph("res/ui/mls_reticle.png");
	_lockOn.cg = ResourceServer::LoadGraph("res/ui/lockon.png");
	Initialize();
}

Camera::~Camera(){

}

void Camera::Initialize(){
	_vPos = VGet(0.f, 10.f, -140.f);
	_oldvPos = _vPos;
	_state = STATE::NORMAL;
	_oldState = _state;
	_cnt = 150;
	_angleH = 0.0f;
	_angleV = 20.0f;

	_lockOn.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - 50;
	_lockOn.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - 50;
}

void Camera::Process(){
	int key = ApplicationMain::GetInstance()->GetKey();  // �L�[���͏��擾
	int trg = ApplicationMain::GetInstance()->GetTrg();  // �L�[���͂̃g���K���擾

	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();  // ��ʉ����T�C�Y�擾
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();  // ��ʏc���T�C�Y�擾

	VECTOR plPos = Player::GetInstance()->GetPos();     // �v���C���[�ʒu���擾
	int plEnergy = Player::GetInstance()->GetEnergy();  // �v���C���[�G�l���M�[�ʎ擾

	VECTOR bsPos = Boss::GetInstance()->GetPos();       // �{�X�ʒu���擾

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly, rx, ry;           // ���E�A�i���O�X�e�B�b�N�̍��W
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);
	rx = static_cast<float>(dinput.Rx);
	ry = static_cast<float>(dinput.Ry);

	float camDis = 25.0f;   // �v���C���[�Ƃ̋���
	float camSpd = 4.0f;    // �J�����ړ����x

#if 1   // 0:�J���p(�J�������R)�A1:�{�ԗp

/**
* �J�����ؑ�
*/
	switch (_state) {

	/**
�@�@* �ʏ���
�@�@*/
	case STATE::NORMAL:
	{	
		if (_oldState != STATE::NORMAL) {
			_vTarg = plPos;
			_vTarg.y = plPos.y + 3.5f;
			float disX = _vPos.x - bsPos.x;
			float disZ = _vPos.z - bsPos.z;
			float rad = atan2(disZ, disX);
			float deg = RAD2DEG(rad);
			_angleH = deg + 90.0f;
		}
		_oldState = _state;

		VECTOR TmpPos1, TmpPos2;
		float sinParam, cosParam;
		_vTarg = plPos;
		_vTarg.y = plPos.y + 3.5f;
/**/
		// �����p�x�𔽉f�����ʒu
		sinParam = sin(_angleV / 180.0f * DX_PI_F);
		cosParam = cos(_angleV / 180.0f * DX_PI_F);
		TmpPos1.x = 0.f;
		TmpPos1.y = 8.5f;       // sinParam * camDis;
		TmpPos1.z = -cosParam * camDis;

		// �����p�x�𔽉f�����ʒu
		sinParam = sin(_angleH / 180.0f * DX_PI_F);
		cosParam = cos(_angleH / 180.0f * DX_PI_F);
		TmpPos2.x = cosParam * TmpPos1.x - sinParam * TmpPos1.z;
		TmpPos2.y = TmpPos1.y;
		TmpPos2.z = sinParam * TmpPos1.x + cosParam * TmpPos1.z;

		// �����p�x�ύX
		if (rx > analogMin) {_angleH -= camSpd; }
		if (rx < -analogMin) { _angleH += camSpd; }
		// �����p�x�ύX
	//	if (ry > analogMin) { _angleV -= camSpd; }
	//	if (ry < -analogMin) { _angleV += camSpd; }

		_vPos = VAdd(TmpPos2, _vTarg);
		
		if (trg & PAD_INPUT_10) { 
			_state = STATE::TARG_LOCK_ON; 
		}
		if (key & PAD_INPUT_5 && plEnergy > 12.5f) {
			_state = STATE::MLS_LOCK;
		}
		break;
	}

	/**
�@�@* �{�X�փJ�������b�N�I�����
�@�@*/
	case STATE::TARG_LOCK_ON:
	{
		_oldState = _state;

		_vTarg = bsPos;
		_vTarg.y = bsPos.y + 3.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float camrad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) + camDis;

		_vPos.x = bsPos.x + cos(camrad) * length;
		_vPos.z = bsPos.z + sin(camrad) * length;
		_vPos.y = plPos.y + 12.0f; // �J���������Œ�

		if(trg & PAD_INPUT_10) {
			_state = STATE::NORMAL;
		}
		if (key & PAD_INPUT_5 && plEnergy > 12.5) {
			_state = STATE::MLS_LOCK;
		}
		break;
	}

	/**
	* �}���`���b�N�I���V�X�e���������
	*/
	case STATE::MLS_LOCK:
	{
		_vTarg = bsPos;
		_vTarg.y = bsPos.y + 3.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float camrad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) - 0.5f;

		_vPos.x = cos(camrad) * length;
		_vPos.z = sin(camrad) * length;
		_vPos.y = plPos.y + 7.0f;

		if (!(key & PAD_INPUT_5)) { _state = STATE::_EOF_; }
		if (plEnergy < 12.5) { _state = STATE::_EOF_; }
		break;
	}
	default:
		if (_oldState == STATE::NORMAL) {
			_state = STATE::NORMAL;
			_oldState = STATE::MLS_LOCK;
		}
		else {
			_state = STATE::TARG_LOCK_ON;
		}
		break;

	}


#else
	if (key & PAD_INPUT_8) {	// W
	// �J�����ʒu�i���ڈʒu��XZ�X���C�h�j
		float sx = _vPos.x - _vTarg.x;
		float sz = _vPos.z - _vTarg.z;
		float camrad = atan2(sz, sx);

		// �ړ����������߂�(���X�e�B�b�N)
		{
			VECTOR vec = { 0,0,0 };
			float mvSpd = 1.f;
			float length = sqrt(lx * lx + ly * ly);
			float rad = atan2(lx, ly);
			if (length < analogMin) {
				// ���͂������������瓮���Ȃ��������Ƃɂ���
				length = 0.f;
			}
			else {
				length = mvSpd;
			}
			// v��rad����]������
			vec.x = cos(rad + camrad) * length;
			vec.z = sin(rad + camrad) * length;

			// vec�̕��ړ�
			_vPos = VAdd(_vPos, vec);
			_vTarg = VAdd(_vTarg, vec);
		}

		// �����A�^�[�Q�b�g�̍����ύX�i�E�X�e�B�b�N�j
		{
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float rad = atan2(sz, sx);
			float length = sqrt(sz * sz + sx * sx);
			if (rx < -analogMin) { length -= 0.5f; }
			if (rx > analogMin) { length += 0.5f; }
			_vPos.x = _vTarg.x + cos(rad) * length;
			_vPos.z = _vTarg.z + sin(rad) * length;

			// Y�ʒu
			if (ry > analogMin) { _vTarg.y -= 0.5f; }
			if (ry < -analogMin) { _vTarg.y += 0.5f; }
		}
	}
	else {
		{
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);

			// �ړ����������߂�
			VECTOR vec = { 0,0,0 };
			float mvSpd = 0.3f;
			// �A�i���O���X�e�B�b�N�p
			float length = sqrt(lx * lx + ly * ly);
			float rad = atan2(lx, ly);
			if (length < analogMin) {
				// ���͂������������瓮���Ȃ��������Ƃɂ���
				length = 0.f;
			}
			else {
				length = mvSpd;
			}

			// v��rad����]������
			vec.x = cos(rad + camrad) * length;
			vec.z = sin(rad + camrad) * length;

			_vPos = VAdd(_vPos, vec);
			_vTarg = VAdd(_vTarg, vec);

			// �J����������s���i�E�X�e�B�b�N�j
			{
				// Y����]
				float sx = _vPos.x - _vTarg.x;
				float sz = _vPos.z - _vTarg.z;
				float rad = atan2(sz, sx);
				float length = sqrt(sz * sz + sx * sx);
				if (rx > analogMin) { rad -= 0.05f; }
				if (rx < -analogMin) { rad += 0.05f; }
				_vPos.x = _vTarg.x + cos(rad) * length;
				_vPos.z = _vTarg.z + sin(rad) * length;

				// Y�ʒu
				if (ry > analogMin) { _vPos.y -= 0.5f; }
				if (ry < -analogMin) { _vPos.y += 0.5f; }
			}
		}
	}
#endif


}


void Camera::Render(){
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(0.1f, 5000.f);

	if (_state == STATE::TARG_LOCK_ON) {
		DrawGraph(_lockOn.x, _lockOn.y, _lockOn.cg, TRUE);
	}
	
#if 1
	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 2.f;
		VECTOR vec = _vTarg;
		DrawLine3D(VAdd(vec, VGet(-linelength, 0, 0)), VAdd(vec, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(vec, VGet(0, -linelength, 0)), VAdd(vec, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(vec, VGet(0, 0, -linelength)), VAdd(vec, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
	{
		int x = 0, y = 0, size = 24;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _vTarg.x, _vTarg.y, _vTarg.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  angleH    = (%5.2f)", _angleH); y += size;
		float disX = _vPos.x - _vTarg.x;
		float disZ = _vPos.z - _vTarg.z;
		float rLength = sqrt(disZ * disZ + disX * disX);
		float rad = atan2(disZ, disX);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", rLength, rad, deg); y += size;
		switch (_state) {
		case STATE::NORMAL:
			DrawString(x, y, "�@��ԁFNORMAL", GetColor(255, 0, 0)); break;
		case STATE::TARG_LOCK_ON:
			DrawString(x, y, "�@��ԁFTARGET_LOCK", GetColor(255, 0, 0)); break;
		case STATE::MLS_LOCK:
			DrawString(x, y, "�@��ԁFMLS_LOCK", GetColor(255, 0, 0)); break;
		}
	}
#endif
}