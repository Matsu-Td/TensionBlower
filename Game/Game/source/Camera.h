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
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetTarg() const { return _vTarg; }

	enum STATE { // �J�����̏��
		NORMAL,      // �ʏ���(TPS���_)
		TARG_LOCK_ON,   // �G�^�[�Q�b�g���b�N���
		MLS_LOCK,    // �}���`���b�N�V�X�e���������(FPS���_)
		_EOF_,
	};

	STATE GetCameraState() { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // �J�����̈ʒu
	VECTOR _oldvPos; // �J�����ʒu�ۑ�
	VECTOR _vTarg;   // �J�����̒����_
	float _angleH;
	float _angleV;
	int _cg;

	STATE _state;    // �J�������

	struct RETICLE { // �\���́F�}���`���b�N�I���V�X�e��
		int x, y;
		int spd;
		int cg;
	};

	struct LOCK_ON { // �\���́F���b�N�I�����
		int x, y;
		int cg;
	};

	RETICLE _reticle; // �}���`���b�N�I���V�X�e���Ə�
	LOCK_ON _lockOn;

	int _cnt;

};
