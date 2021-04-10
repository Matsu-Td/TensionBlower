/**
 * @file   Dash.cpp
 * @brief  プレイヤーダッシュ処理
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"

/*
 * 移動、ダッシュモーション切替処理
 */
void Player::LeftAnalogDeg() {

	if (!_canJump) {
		return;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_isDash) {
		// ダッシュ用移動速度セット
		_mvSpd = modeGame->_charaData->_mvSpdDash;
		// 前方向ダッシュ移動
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = Player::STATE::FOR_DASH;
		}
		// 左方向ダッシュ移動
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = Player::STATE::LEFT_DASH;

		}
		// 右方向ダッシュ移動
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = Player::STATE::RIGHT_DASH;

		}
		// 後方向ダッシュ移動
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER && _analogLength >= ANALOG_MIN) {
			_state = Player::STATE::BACK_DASH;
		}
		// 入力がゲームパッド「RB」のみ場合は前方向ダッシュ移動
		else {
			_state = Player::STATE::FOR_DASH;
		}
	}
	else {
		// 通常移動速度セット
		_mvSpd = modeGame->_charaData->_mvSpdNorm;
		// 前方向移動
		if (_lfAnalogDeg >= ANALOG_REG_FOR || _lfAnalogDeg <= -ANALOG_REG_FOR) {
			_state = Player::STATE::WALK;
		}
		// 左方向移動
		else if (_lfAnalogDeg < -ANALOG_REG_OTHER && _lfAnalogDeg > -ANALOG_REG_FOR) {
			_state = Player::STATE::LEFT_MOVE;
		}
		// 右方向移動
		else if (_lfAnalogDeg > ANALOG_REG_OTHER && _lfAnalogDeg < ANALOG_REG_FOR) {
			_state = Player::STATE::RIGHT_MOVE;
		}
		// 後方向移動
		else if (_lfAnalogDeg >= -ANALOG_REG_OTHER && _lfAnalogDeg <= ANALOG_REG_OTHER) {
			_state = Player::STATE::BACK_MOVE;
		}
	}
}

/*
 * ダッシュ処理
 */
void Player::Dash() {
	
	int key = ApplicationMain::GetInstance()->GetKey();// キー入力情報取得
	int trg = ApplicationMain::GetInstance()->GetTrg();// キーのトリガ情報取得

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // カメラの状態

	// 現在のプレイヤーの正面角度
	float nowAngle = atan2(_vDir.z, _vDir.x);

	// 短押しダッシュ
	VECTOR vDash{ 0.0f,0.0f,00.f };      // ダッシュする方向
	if (trg & PAD_INPUT_6 && (_state != Player::STATE::JUMP) && _energy > modeGame->_charaData->_egDash) {
		_mvSpd = modeGame->_charaData->_mvSpdDash;  // ダッシュ移動速度セット
		_isShortDash = true;              // 短押しダッシュ移動スタート
		_canLongDash = true;              // 短押しダッシュ発動 ⇒ 長押しダッシュ発動可能となる
		_shortDashTime = SHORT_DASH_CNT;  // 短押しダッシュ移動時間をセット

	}
	if (_isShortDash) {
		_shortDashTime--;
		if (_shortDashTime > 0) {
			_isDash = true;  // ダッシュスタート
			// キー入力があるとき入力方向にダッシュする
			if (camState != Camera::STATE::NORMAL) {
				_state = Player::STATE::FOR_DASH;
			}
			_isCharging = false;   // ダッシュ中溜め行動不可
			// キー入力がないとき向いている方向に直線でダッシュする
			if (_analogLength < ANALOG_MIN) {
				if (camState == Camera::STATE::NORMAL) {
					LeftAnalogDeg();
					vDash.x = -cos(_bsAngle) * _mvSpd;
					vDash.z = -sin(_bsAngle) * _mvSpd;
				}
				else {
					vDash.x = cos(nowAngle) * _mvSpd;
					vDash.z = sin(nowAngle) * _mvSpd;
				}
				_vPos.x += vDash.x;
				_vPos.z += vDash.z;
			}
		}
		else {
			_shortDashTime = 0;
			_isShortDash = false;
			_isDash = false;
		}
	}
	// 長押しダッシュ
	if (key & PAD_INPUT_6) {
		//プレイヤーが地上にいる 、長押しダッシュ可能(短押しダッシュを行った時)、短押しダッシュ移動が終わっている、エネルギー0よりある
		if (_canJump && _canLongDash && !_isShortDash && _energy > 0) {
			_isDash = true;       // ダッシュ状態にする
			_isCharging = false;  // ダッシュ中溜め行動不可
			// キー入力があるときが入力方向にダッシュする
			if (camState != Camera::STATE::NORMAL) {
				_state = Player::STATE::FOR_DASH;
			}
			// キー入力がないとき：向いている方向に直線でダッシュする
			if (_analogLength < ANALOG_MIN) {
				if (camState == Camera::STATE::NORMAL) {
					LeftAnalogDeg();
					vDash.x = -cos(_bsAngle) * _mvSpd;
					vDash.z = -sin(_bsAngle) * _mvSpd;
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
				else {
					vDash.x = cos(nowAngle) * _mvSpd;
					vDash.z = sin(nowAngle) * _mvSpd;
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
			}
		}
	}
	else {
		_isDash = false;
		_canLongDash = false;
	}
}