/**
 * @file   Camera.cpp
 * @brief  �J�����N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "Camera.h"
#include "../Application/ApplicationMain.h"
#include "../Player/Player.h"
#include "../Boss/Boss.h"

using namespace tensionblower::camera;

Camera* Camera::_pInstance = nullptr;

Camera::Camera(){

	_pInstance = this;
	_lockOn.cg = ResourceServer::LoadGraph("res/ui/player/lockon.png");

	Initialize();
}

Camera::~Camera(){
	// �������Ȃ�
}

/*
 * ������
 */
void Camera::Initialize(){

	_vPos = VGet(0.0f, 10.0f, -140.f);
	_state = STATE::NORMAL;

	int graphSizeX, graphSizeY;
	GetGraphSize(_lockOn.cg, &graphSizeX, &graphSizeY);

	_lockOn.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - (graphSizeX / 2);
	_lockOn.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - (graphSizeY / 2);
}

/*
 * �J�����̌����Ă���p�x(rad)�擾
 */
float Camera::GetRad() const {

	float disX = _vPos.x - _vTarg.x;
	float disZ = _vPos.z - _vTarg.z;
	float camRad = atan2(disZ, disX);

	return camRad;
}

/*
 * �J�����̈ʒu�ݒ�
 */
void Camera::SetPos(float dis, float height) {

	VECTOR bsPos = Boss::GetInstance()->GetPos();       // �{�X�ʒu���擾
	VECTOR plPos = player::Player::GetInstance()->GetPos();     // �v���C���[�ʒu���擾

	float sx = plPos.x - _vTarg.x;
	float sz = plPos.z - _vTarg.z;
	float rad = atan2(sz, sx);
	float length = Util::Sqrt(sx, sz) + dis;

	_vPos.x = bsPos.x + cos(rad) * length;
	_vPos.z = bsPos.z + sin(rad) * length;
	_vPos.y = plPos.y + height;
}

/*
 * �ʏ��Ԃ̏���
 */
void Camera::StateNorm() {

	int key = ApplicationMain::GetInstance()->GetKey(); // �L�[���͏��擾

	int plEnergy = player::Player::GetInstance()->GetEnergy();  // �v���C���[�G�l���M�[�ʎ擾

	float dis = 25.0f;   // �v���C���[�Ƃ̋���
	float height = 15.0f;

	SetPos(dis, height);

	// �Q�[���p�b�h�uLB�v�������ŃJ������FPS���_(�}���`���b�N�V�X�e������)�ɐؑ�
	if (key & PAD_INPUT_5 && plEnergy > 10) {
		_state = STATE::MLS_LOCK;
	}
}

/*
 * �}���`���b�N�I���V�X�e���������̏���
 */
void Camera::StateMLSLock() {

	int key = ApplicationMain::GetInstance()->GetKey(); // �L�[���͏��擾

	int plEnergy = player::Player::GetInstance()->GetEnergy();  // �v���C���[�G�l���M�[�ʎ擾

	float dis = -2.5f;   // �v���C���[�Ƃ̋���
	float height = 7.0f;

	SetPos(dis, height);

	if (!(key & PAD_INPUT_5)) {
		_state = STATE::NORMAL;
	}
	if (plEnergy < 10) {
		_state = STATE::NORMAL;
	}
}

/*
 * �t���[�������F�v�Z
 */
void Camera::Process(){

	VECTOR bsPos = Boss::GetInstance()->GetPos();  // �{�X�ʒu���擾

	// �����_�̓{�X�ɌŒ�
	_vTarg = bsPos;
	_vTarg.y = 8.5f;

    // �J�����ؑ�
	switch (_state) {
	case STATE::NORMAL:
		StateNorm();

		break;

	case STATE::MLS_LOCK:
		StateMLSLock();

		break;
	}
}

/*
 * �t���[�������F�`��
 */
void Camera::Render(){

	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(NEAR_CLIP, FAR_CLIP);

	if (_state == STATE::NORMAL) {
		DrawGraph(_lockOn.x, _lockOn.y, _lockOn.cg, TRUE);
	}

#ifdef _DEBUG
	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 2.0f;
		VECTOR vec = _vTarg;
		DrawLine3D(VAdd(vec, VGet(-linelength, 0, 0)), VAdd(vec, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(vec, VGet(0, -linelength, 0)), VAdd(vec, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(vec, VGet(0, 0, -linelength)), VAdd(vec, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
	{
		int x = 0, y = 200, fontSize = 24;
		int fontColor = GetColor(255, 0, 0);
		SetFontSize(fontSize);
		DrawFormatString(x, y, fontColor, "Camera:"); y += fontSize;
		DrawFormatString(x, y, fontColor, "  target = (%5.2f, %5.2f, %5.2f)", _vTarg.x, _vTarg.y, _vTarg.z); y += fontSize;
		DrawFormatString(x, y, fontColor, "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += fontSize;
		float sx = _vPos.x - _vTarg.x;
		float sz = _vPos.z - _vTarg.z;
		float length = Util::Sqrt(sx, sz);
		float rad = atan2(sz, sx);
		float deg = Util::RadToDeg(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += fontSize;
		switch (_state) {
		case STATE::NORMAL:
			DrawString(x, y, "�@��ԁFTARGET_LOCK", fontColor); break;
		case STATE::MLS_LOCK:
			DrawString(x, y, "�@��ԁFMLS_LOCK", fontColor); break;
		}
	}
#endif
}