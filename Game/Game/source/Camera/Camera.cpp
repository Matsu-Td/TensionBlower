/**
 * @file   Camera.cpp
 * @brief  カメラクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "Camera.h"
#include "../Application/ApplicationMain.h"
#include "../Player/Player.h"
#include "../Boss/Boss.h"

Camera* Camera::_pInstance = nullptr;

Camera::Camera(){

	_pInstance = this;
	_lockOn.cg = ResourceServer::LoadGraph("res/ui/player/lockon.png");
	Initialize();
}

Camera::~Camera(){
	// 何もしない
}

float Camera::GetRad() const {

	float disX = _vPos.x - _vTarg.x;
	float disZ = _vPos.z - _vTarg.z;
	float camRad = atan2(disZ, disX);

	return camRad;
}

/*
 * 初期化
 */
void Camera::Initialize(){

	_vPos = VGet(0.0f, 10.0f, -140.f);
	_oldvPos = _vPos;
	_state = STATE::NORMAL;
	_oldState = _state;

	_lockOn.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - 50;
	_lockOn.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - 50;
}

/*
 * フレーム処理：計算
 */
void Camera::Process(){

	int key = ApplicationMain::GetInstance()->GetKey();  // キー入力情報取得

	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();  // 画面横幅サイズ取得
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();  // 画面縦幅サイズ取得

	VECTOR plPos = Player::GetInstance()->GetPos();     // プレイヤー位置情報取得
	int plEnergy = Player::GetInstance()->GetEnergy();  // プレイヤーエネルギー量取得

	VECTOR bsPos = Boss::GetInstance()->GetPos();       // ボス位置情報取得

	float camDis = 25.0f;   // プレイヤーとの距離
	float camSpd = 4.0f;    // カメラ移動速度

    // カメラ切替
	switch (_state) {
	// ボスへカメラロックオン状態
	case STATE::NORMAL:
	{
		_oldState = _state;

		_vTarg = bsPos;
		_vTarg.y = 8.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) + camDis;

		_vPos.x = bsPos.x + cos(rad) * length;
		_vPos.z = bsPos.z + sin(rad) * length;
		_vPos.y = plPos.y + 15.0f; 
		
		// ゲームパッド「LB」長押しでカメラをFPS視点(マルチロックシステム発動)に切替
		if (key & PAD_INPUT_5 && plEnergy > 10) {
			_state = STATE::MLS_LOCK;
		}
		break;
	}

	// マルチロックオンシステム発動状態
	case STATE::MLS_LOCK:
	{
		_vTarg = bsPos;
		_vTarg.y = 8.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) - 2.5f;

		_vPos.x = cos(rad) * length;
		_vPos.z = sin(rad) * length;
		_vPos.y = plPos.y + 7.0f;

		if (!(key & PAD_INPUT_5)) { 
			_state = STATE::NORMAL; 
		}
		if (plEnergy < 10) { 
			_state = STATE::NORMAL;
		}
		break;
	}
	}
}

/*
 * フレーム処理：描画
 */
void Camera::Render(){

	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(NearClip, FarClip);

	if (_state == STATE::NORMAL) {
		DrawGraph(_lockOn.x, _lockOn.y, _lockOn.cg, TRUE);
	}

#ifdef _DEBUG
	// カメラターゲットを中心に短い線を引く
	{
		float linelength = 2.f;
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
		float disX = _vPos.x - _vTarg.x;
		float disZ = _vPos.z - _vTarg.z;
		float rLength = sqrt(disZ * disZ + disX * disX);
		float rad = atan2(disZ, disX);
		float deg = Util::RadToDeg(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", rLength, rad, deg); y += fontSize;
		switch (_state) {
		case STATE::NORMAL:
			DrawString(x, y, "　状態：TARGET_LOCK", fontColor); break;
		case STATE::MLS_LOCK:
			DrawString(x, y, "　状態：MLS_LOCK", fontColor); break;
		}
	}
#endif
}