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

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // カメラの位置
	VECTOR _vTarg;   // カメラの注視点

	enum class STATE {
		NORMAL,
		LOCK,
		MRS_LOCK,
	};
	STATE _state;
};
