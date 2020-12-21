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
	VECTOR _vPos;    // カメラの位置
	VECTOR _oldvPos; // カメラ位置保存
	VECTOR _vTarg;   // カメラの注視点

	enum STATE { // カメラの状態
		NORMAL,   // 通常状態(TPS視点)
		LOCK,     // 敵へカメラロック状態
		MRS_LOCK, // マルチロックシステム発動(FPS視点)
		_EOF_,
	};
	int _state;

};
