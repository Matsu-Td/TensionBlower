/** 
 * @file   Move.cpp
 * @brief  プレイヤーの移動処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

/*
 * 移動処理
 */
void Player::Move() {

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);

	// 左アナログスティック座標
	float lx, ly;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// カメラデータ取得
	VECTOR camPos = Camera::GetInstance()->GetPos();      // カメラ位置
	VECTOR camTarg = Camera::GetInstance()->GetTarg();    // カメラの注視点

	// カメラの向いている角度取得
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// 移動方向を決める
	VECTOR vec = { 0.0f,0.0f,0.0f };
	_analogLength = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);


	// 移動処理
	if (_analogLength < ANALOG_MIN) {
		_analogLength = 0.0f;
	}
	else {
		_analogLength = _mvSpd;
	}

	// vecをrad分回転させる
	vec.x = cos(rad + camRad) * _analogLength;
	vec.z = sin(rad + camRad) * _analogLength;

	// vecの分移動
	_vPos = VAdd(_vPos, vec);

	// 移動量をそのままキャラの向きにする
	if (VSize(vec) > 0.0f) {		// 移動していない時は無視する
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		LeftAnalogDeg();

		if (!_isDash) {
			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
		}

	}
	else if (_canJump && !_isAttack) {
		_state = STATE::WAIT;
	}
}


