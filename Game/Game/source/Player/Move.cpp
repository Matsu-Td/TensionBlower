/** 
 * @file   Move.cpp
 * @brief  プレイヤーの移動処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::player;

/*
 * 移動処理
 */
void Player::Move() {

	VECTOR camPos  = camera::Camera::GetInstance()->GetPos();   // カメラ位置
	VECTOR camTarg = camera::Camera::GetInstance()->GetTarg();  // カメラの注視点
	float camRad   = camera::Camera::GetInstance()->GetRad();   // カメラの向いている角度取得

	float length = util::GetLeftStickLength(); 	// 左スティックの移動量
	float rad    = util::GetLeftStickRad();     // 左スティックの角度(rad)

	VECTOR vec = { 0.0f,0.0f,0.0f };

	// 移動処理
	if (length < util::ANALOG_MIN) {
		length = 0.0f;
	}
	else {
		length = _mvSpd;
	}

	// vecをrad分回転させる
	vec.x = cos(rad + camRad) * length;
	vec.z = sin(rad + camRad) * length;

	// vecの分移動
	_vPos = VAdd(_vPos, vec);

	// 移動量をそのままキャラの向きにする
	if (VSize(vec) > 0.0f) {		// 移動していない時は無視する
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		MoveAndDashMotionSwitch();

		if (!_isDash) {
			mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
			_mvSpd = modeGame->_charaData->_mvSpdNorm;
		}
	}
	else if (_canJump && !_isAttack) {
		_state = STATE::WAIT;
	}
}


