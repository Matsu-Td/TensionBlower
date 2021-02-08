#pragma once

/**
 * @file  Camera.h
 * @brief カメラ関連処理
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

	enum STATE { // カメラの状態
		NORMAL,      // 通常状態(TPS視点)
		TARG_LOCK_ON,   // 敵ターゲットロック状態
		MLS_LOCK,    // マルチロックシステム発動状態(FPS視点)
		_EOF_,
	};
	STATE _state;    // カメラ状態
	STATE GetCameraState() { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // カメラの位置
	VECTOR _oldvPos; // カメラ位置保存
	VECTOR _vTarg;   // カメラの注視点
	float _angleH;
	float _angleV;
	int _cg;

	STATE _oldState;

	struct LOCK_ON { // 構造体：ロックオン状態
		int x, y;
		int cg;
	};
	LOCK_ON _lockOn;

	int _cnt;
};
