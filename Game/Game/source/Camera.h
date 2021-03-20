/**
 * @file   Camera.h
 * @brief  カメラ関連処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#pragma once

#include "appframe.h"

#define	DEG2RAD(x)			( ((x) / 180.0f ) * DX_PI_F )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / DX_PI_F )

class Camera{
public:
	Camera();
	~Camera();

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

	static Camera* GetInstance() { return _pInstance; }

	/**
	 * @brief 座標取得
	 * 
	 * @return 座標
	 */
	VECTOR GetPos() const { return _vPos; }

	/**
	 * @brief ターゲット座標取得
	 * 
	 * @return ターゲット座標
	 */
	VECTOR GetTarg() const { return _vTarg; }

	enum class STATE {      // カメラの状態
		TARG_LOCK_ON, // 敵ターゲットロック状態(デフォルト)
		MLS_LOCK,     // マルチロックシステム発動状態(FPS視点)
	};
	STATE _state;    // カメラ状態
	STATE GetCameraState() { return _state; }

	static Camera* _pInstance;

private:
	VECTOR _vPos;    // 位置
	VECTOR _oldvPos; // 処理前の位置
	VECTOR _vTarg;   // 注視点
	float _angleH;   // 水平角度
	float _angleV;   // 垂直角度

	STATE _oldState; // 処理前の状態

	struct LOCK_ON { // 構造体：ロックオン状態
		int x, y;  // スクリーン座標
		int cg;    // 画像
	};
	LOCK_ON _lockOn;
};
