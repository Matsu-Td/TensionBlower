#pragma once

/**
 * @file  Camera.h
 * @brief �J�����֘A����
 *
 * @date 2021-02-08
 */

#include "appframe.h"

#define	DEG2RAD(x)			( ((x) / 180.0f ) * DX_PI_F )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / DX_PI_F )

class Camera{
public:
	Camera();
	~Camera();

	void Initialize();
	void Process();
	void Render();

	static Camera* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetTarg() const { return _vTarg; }

	enum STATE { // �J�����̏��
		NORMAL,      // �ʏ���(TPS���_)
		TARG_LOCK_ON,   // �G�^�[�Q�b�g���b�N���
		MLS_LOCK,    // �}���`���b�N�V�X�e���������(FPS���_)
		_EOF_,
	};
	STATE _state;    // �J�������
	STATE GetCameraState() { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // �ʒu
	VECTOR _oldvPos; // �����O�̈ʒu
	VECTOR _vTarg;   // �����_
	float _angleH;   // �����p�x
	float _angleV;   // �����p�x

	STATE _oldState; // �����O�̏��

	struct LOCK_ON { // �\���́F���b�N�I�����
		int x, y;  // �X�N���[�����W
		int cg;    // �摜
	};
	LOCK_ON _lockOn;
};
