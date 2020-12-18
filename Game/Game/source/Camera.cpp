#include "Camera.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "Boss.h"

Camera* Camera::_pInstance = NULL;
#define TEST 0

Camera::Camera()
{
	_pInstance = this;
	Initialize();
}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	_vPos = VGet(0.f, 10.f, -140.f);
	_state = STATE::NORMAL;
}

void Camera::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	VECTOR plPos = Player::GetInstance()->GetPos();   // �v���C���[�ʒu���擾
	VECTOR bsPos = Boss::GetInstance()->GetPos();   // �{�X�ʒu���擾

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly, rx, ry;           // ���E�A�i���O�X�e�B�b�N�̍��W
	float analogMin = 0.3f; 
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);
	rx = static_cast<float>(dinput.Rx);
	ry = static_cast<float>(dinput.Ry);




	// �J�����ړ�����
#if TEST
	if (_vPos.y >= 20.f) {
		_vPos.y = 20.f;
	}
	if (_vPos.y < 2.5f) {
		_vPos.y = 2.5f;
	}
#endif

/*	if (trg & PAD_INPUT_3) {   // �J�����̈ʒu�������ʒu�ɖ߂�
		Initialize();
	}
*/
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

		switch(_state){
		case STATE::NORMAL:
		{
			_vTarg = VGet(plPos.x, plPos.y + 3.5f, plPos.z);
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);

			/*
			float sx = _vPos.x - _vTarg.x;
			float sz = _vPos.z - _vTarg.z;
			float camrad = atan2(sz, sx);
			*/
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
			break;
		}
		case STATE::LOCK:
			break;
		default:
			break;

		}
	}


	// �G�ւ̃J�������b�N�I���I�t�ؑ�
	if (trg & PAD_INPUT_10) {           // �E�A�i���O�X�e�B�b�N��������
		if (_state == STATE::NORMAL) {
			_state = STATE::LOCK;
		}
		else {
			_state = STATE::NORMAL;
		}
	}

}


void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(0.1f, 5000.f);

#ifdef _DEBUG
	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 2.f;
		VECTOR vec = _vTarg;
		DrawLine3D(VAdd(vec, VGet(-linelength, 0, 0)), VAdd(vec, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(vec, VGet(0, -linelength, 0)), VAdd(vec, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(vec, VGet(0, 0, -linelength)), VAdd(vec, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
	{
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _vTarg.x, _vTarg.y, _vTarg.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
		float disX = _vPos.x - _vTarg.x;
		float disZ = _vPos.z - _vTarg.z;
		float rLength = sqrt(disZ * disZ + disX * disX);
		float rad = atan2(disZ, disX);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", rLength, rad, deg); y += size;
	}
#endif
}
