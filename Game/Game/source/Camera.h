#pragma once
#include "appframe.h"

#define	DEG2RAD(x)			( ((x) / 180.0f ) * DX_PI_F )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / DX_PI_F )

class Camera
{
public:
	Camera();
	~Camera();

	void Initialize();
	void Process();
	void Render();



	static Camera* GetInstance() { return _pInstance; }
	VECTOR GetPos() { return _vPos; }
	VECTOR GetTarg() { return _vTarg; }
	int GetCameraState() { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // �J�����̈ʒu
	VECTOR _oldvPos; // �J�����ʒu�ۑ�
	VECTOR _vTarg;   // �J�����̒����_

	enum STATE { // �J�����̏��
		NORMAL,   // �ʏ���(TPS���_)
		LOCK,     // �G�փJ�������b�N���
		MRS_LOCK, // �}���`���b�N�V�X�e������(FPS���_)
		_EOF_,
	};
	int _state;

};
