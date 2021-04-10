/**
 * @file   Camera.h
 * @brief  カメラクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"

/**
 * @brief カメラクラス
 */
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

	/**
	 * インスタンスを取得
	 * @return Cameraのインスタンス
	 */
	static Camera* GetInstance() { return _pInstance; }

	/**
	 * @brief 座標取得
	 * @return 座標
	 */
	VECTOR GetPos() const { return _vPos; }

	/**
	 * @brief  ターゲット座標取得
	 * @return ターゲット座標
	 */
	VECTOR GetTarg() const { return _vTarg; }

	/**
	 * @brief カメラの状態
	 */
	enum class STATE { 
		NORMAL,    // 敵ターゲットロック状態(デフォルト)
		MLS_LOCK,  // マルチロックシステム発動状態(FPS視点)
	};
	STATE _state;  // カメラ状態

	/**
	 * @brief  カメラの状態を取得
	 * @return カメラの状態
	 */
	STATE GetCameraState() const { return _state; }

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

	const float NearClip = 0.1f;
	const float FarClip  = 5000.0f;
};
