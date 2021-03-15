/**
 * @file   Camera.cpp
 * @brief  カメラ関連処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Camera.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "Boss.h"

Camera* Camera::_pInstance = NULL;

Camera::Camera(){

	_pInstance = this;
	_lockOn.cg = ResourceServer::LoadGraph("res/ui/player/lockon.png");
	Initialize();
}

Camera::~Camera(){

}

/**
 * 初期化
 */
void Camera::Initialize(){

	_vPos = VGet(0.f, 10.f, -140.f);
	_oldvPos = _vPos;
	_state = STATE::NORMAL;
	_oldState = _state;
	_angleH = 0.0f;
	_angleV = 20.0f;

	_lockOn.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - 50;
	_lockOn.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - 50;
}

/**
 * フレーム処理：計算
 */
void Camera::Process(){

	int key = ApplicationMain::GetInstance()->GetKey();  // キー入力情報取得
	int trg = ApplicationMain::GetInstance()->GetTrg();  // キー入力のトリガ情報取得

	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();  // 画面横幅サイズ取得
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();  // 画面縦幅サイズ取得

	VECTOR plPos = Player::GetInstance()->GetPos();     // プレイヤー位置情報取得
	int plEnergy = Player::GetInstance()->GetEnergy();  // プレイヤーエネルギー量取得

	VECTOR bsPos = Boss::GetInstance()->GetPos();       // ボス位置情報取得

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly, rx, ry;           // 左右アナログスティックの座標
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);
	rx = static_cast<float>(dinput.Rx);
	ry = static_cast<float>(dinput.Ry);

	float camDis = 25.0f;   // プレイヤーとの距離
	float camSpd = 4.0f;    // カメラ移動速度

    // カメラ切替
	switch (_state) {

	// 通常状態
	case STATE::NORMAL:
	{	
		if (_oldState != STATE::NORMAL) {
			_vTarg = plPos;
			_vTarg.y = plPos.y + 3.5f;
			float disX = _vPos.x - bsPos.x;
			float disZ = _vPos.z - bsPos.z;
			float rad = atan2(disZ, disX);
			float deg = RAD2DEG(rad);
			_angleH = deg + 90.0f;
		}
		_oldState = _state;

		VECTOR tmpPos1, tmpPos2;
		float sinParam, cosParam;
		_vTarg = plPos;
		_vTarg.y = plPos.y + 3.5f;

		// 垂直角度を反映した位置
		sinParam = sin(_angleV / 180.0f * DX_PI_F);
		cosParam = cos(_angleV / 180.0f * DX_PI_F);
		tmpPos1.x = 0.f;
		tmpPos1.y = 8.5f;   // ボスの中心の高さ   
		tmpPos1.z = -cosParam * camDis;

		// 水平角度を反映した位置
		sinParam = sin(_angleH / 180.0f * DX_PI_F);
		cosParam = cos(_angleH / 180.0f * DX_PI_F);
		tmpPos2.x = cosParam * tmpPos1.x - sinParam * tmpPos1.z;
		tmpPos2.y = tmpPos1.y;
		tmpPos2.z = sinParam * tmpPos1.x + cosParam * tmpPos1.z;

		// 水平角度変更
		if (rx > analogMin)  { _angleH -= camSpd; }
		if (rx < -analogMin) { _angleH += camSpd; }

		_vPos = VAdd(tmpPos2, _vTarg);
		
		// ゲームパッド右アナログスティック押し込みでボスへカメラロック
		if (trg & PAD_INPUT_10) { 
			_state = STATE::TARG_LOCK_ON; 
		}
		// ゲームパッド「LB」長押しでカメラをFPS視点(マルチロックシステム発動)に切替
		if (key & PAD_INPUT_5 && plEnergy > 10) {
			_state = STATE::MLS_LOCK;
		}
		break;
	}

	/**
　　 * ボスへカメラロックオン状態
　　 */
	case STATE::TARG_LOCK_ON:
	{
		_oldState = _state;

		_vTarg = bsPos;
		_vTarg.y = bsPos.y + 8.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float camrad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) + camDis;

		_vPos.x = bsPos.x + cos(camrad) * length;
		_vPos.z = bsPos.z + sin(camrad) * length;
		_vPos.y = plPos.y + 14.0f; 
		
		// ゲームパッド右アナログスティック押し込みでロック解除
		if (trg & PAD_INPUT_10) {
			_state = STATE::NORMAL;
		}
		// ゲームパッド「LB」長押しでカメラをFPS視点(マルチロックシステム発動)に切替
		if (key & PAD_INPUT_5 && plEnergy > 10.0f) {
			_state = STATE::MLS_LOCK;
		}
		break;
	}

	/**
	 * マルチロックオンシステム発動状態
	 */
	case STATE::MLS_LOCK:
	{
		_vTarg = bsPos;
		_vTarg.y = bsPos.y + 3.5f;
		float sx = plPos.x - _vTarg.x;
		float sz = plPos.z - _vTarg.z;
		float camrad = atan2(sz, sx);
		float length = sqrt(sx * sx + sz * sz) - 2.5f;

		_vPos.x = cos(camrad) * length;
		_vPos.z = sin(camrad) * length;
		_vPos.y = plPos.y + 7.0f;

		if (!(key & PAD_INPUT_5)) { _state = STATE::_EOF_; }
		if (plEnergy < 10) { _state = STATE::_EOF_; }
		break;
	}
	default:
		if (_oldState == STATE::NORMAL) {
			_state = STATE::NORMAL;
			_oldState = STATE::MLS_LOCK;
		}
		else {
			_state = STATE::TARG_LOCK_ON;
		}
		break;
	}
}

/**
 * フレーム処理：描画
 */
void Camera::Render(){

	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(0.1f, 5000.f);

	if (_state == STATE::TARG_LOCK_ON) {
		DrawGraph(_lockOn.x, _lockOn.y, _lockOn.cg, TRUE);
	}

#if 0
	// カメラターゲットを中心に短い線を引く
	{
		float linelength = 2.f;
		VECTOR vec = _vTarg;
		DrawLine3D(VAdd(vec, VGet(-linelength, 0, 0)), VAdd(vec, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(vec, VGet(0, -linelength, 0)), VAdd(vec, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(vec, VGet(0, 0, -linelength)), VAdd(vec, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
	{
		int x = 0, y = 200, size = 24;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _vTarg.x, _vTarg.y, _vTarg.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  angleH    = (%5.2f)", _angleH); y += size;
		float disX = _vPos.x - _vTarg.x;
		float disZ = _vPos.z - _vTarg.z;
		float rLength = sqrt(disZ * disZ + disX * disX);
		float rad = atan2(disZ, disX);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", rLength, rad, deg); y += size;
		switch (_state) {
		case STATE::NORMAL:
			DrawString(x, y, "　状態：NORMAL", GetColor(255, 0, 0)); break;
		case STATE::TARG_LOCK_ON:
			DrawString(x, y, "　状態：TARGET_LOCK", GetColor(255, 0, 0)); break;
		case STATE::MLS_LOCK:
			DrawString(x, y, "　状態：MLS_LOCK", GetColor(255, 0, 0)); break;
		}
	}
#endif
}