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

using namespace tensionblower::camera;

Camera* Camera::_pInstance = nullptr;

Camera::Camera(){

	_pInstance = this;
	_lockOn.cg = ResourceServer::LoadGraph("res/ui/player/lockon.png");

	Initialize();
}

Camera::~Camera(){
	// 何もしない
}

/*
 * 初期化
 */
void Camera::Initialize(){

	_vPos = VGet(0.0f, 10.0f, -140.f);
	_state = STATE::NORMAL;

	int graphSizeX, graphSizeY;
	GetGraphSize(_lockOn.cg, &graphSizeX, &graphSizeY);

	_lockOn.x = ApplicationMain::GetInstance()->DispSizeW() / 2 - (graphSizeX / 2);
	_lockOn.y = ApplicationMain::GetInstance()->DispSizeH() / 2 - (graphSizeY / 2);
}

/*
 * カメラの向いている角度(rad)取得
 */
float Camera::GetRad() const {

	float disX = _vPos.x - _vTarg.x;
	float disZ = _vPos.z - _vTarg.z;
	float camRad = atan2(disZ, disX);

	return camRad;
}

/*
 * カメラの位置設定
 */
void Camera::SetPos(float dis, float height) {

	VECTOR bsPos = Boss::GetInstance()->GetPos();       // ボス位置情報取得
	VECTOR plPos = player::Player::GetInstance()->GetPos();     // プレイヤー位置情報取得

	float sx = plPos.x - _vTarg.x;
	float sz = plPos.z - _vTarg.z;
	float rad = atan2(sz, sx);
	float length = Util::Sqrt(sx, sz) + dis;

	_vPos.x = bsPos.x + cos(rad) * length;
	_vPos.z = bsPos.z + sin(rad) * length;
	_vPos.y = plPos.y + height;
}

/*
 * 通常状態の処理
 */
void Camera::StateNorm() {

	int key = ApplicationMain::GetInstance()->GetKey(); // キー入力情報取得

	int plEnergy = player::Player::GetInstance()->GetEnergy();  // プレイヤーエネルギー量取得

	float dis = 25.0f;   // プレイヤーとの距離
	float height = 15.0f;

	SetPos(dis, height);

	// ゲームパッド「LB」長押しでカメラをFPS視点(マルチロックシステム発動)に切替
	if (key & PAD_INPUT_5 && plEnergy > 10) {
		_state = STATE::MLS_LOCK;
	}
}

/*
 * マルチロックオンシステム発生中の処理
 */
void Camera::StateMLSLock() {

	int key = ApplicationMain::GetInstance()->GetKey(); // キー入力情報取得

	int plEnergy = player::Player::GetInstance()->GetEnergy();  // プレイヤーエネルギー量取得

	float dis = -2.5f;   // プレイヤーとの距離
	float height = 7.0f;

	SetPos(dis, height);

	if (!(key & PAD_INPUT_5)) {
		_state = STATE::NORMAL;
	}
	if (plEnergy < 10) {
		_state = STATE::NORMAL;
	}
}

/*
 * フレーム処理：計算
 */
void Camera::Process(){

	VECTOR bsPos = Boss::GetInstance()->GetPos();  // ボス位置情報取得

	// 注視点はボスに固定
	_vTarg = bsPos;
	_vTarg.y = 8.5f;

    // カメラ切替
	switch (_state) {
	case STATE::NORMAL:
		StateNorm();

		break;

	case STATE::MLS_LOCK:
		StateMLSLock();

		break;
	}
}

/*
 * フレーム処理：描画
 */
void Camera::Render(){

	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarg);
	SetCameraNearFar(NEAR_CLIP, FAR_CLIP);

	if (_state == STATE::NORMAL) {
		DrawGraph(_lockOn.x, _lockOn.y, _lockOn.cg, TRUE);
	}

#ifdef _DEBUG
	// カメラターゲットを中心に短い線を引く
	{
		float linelength = 2.0f;
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
		float sx = _vPos.x - _vTarg.x;
		float sz = _vPos.z - _vTarg.z;
		float length = Util::Sqrt(sx, sz);
		float rad = atan2(sz, sx);
		float deg = Util::RadToDeg(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += fontSize;
		switch (_state) {
		case STATE::NORMAL:
			DrawString(x, y, "　状態：TARGET_LOCK", fontColor); break;
		case STATE::MLS_LOCK:
			DrawString(x, y, "　状態：MLS_LOCK", fontColor); break;
		}
	}
#endif
}