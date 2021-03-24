/**
 * @file   PlayerDash.cpp
 * @brief  プレイヤーダッシュ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerDash.h"

PlayerDash::PlayerDash() {

}

/**
 * カメラロック中の移動、ダッシュモーション,移動射撃モーション切替処理
 * 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
 */
void PlayerDash::LeftAnalogDeg(Player* player, float length) {

	if (!player->_canJump) {
		return;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_isDash) {
		// ダッシュ用移動速度セット
		player->_mvSpd = modeGame->_charaData->_mvSpdDash;
		// 前方向ダッシュ移動
		if (player->_lfAnalogDeg >= ANALOG_REG_FOR || player->_lfAnalogDeg <= -ANALOG_REG_FOR) {
			player->_state = Player::STATE::FOR_DASH;
		}
		// 左方向ダッシュ移動
		else if (player->_lfAnalogDeg < -ANALOG_REG_OTHER && player->_lfAnalogDeg > -ANALOG_REG_FOR) {
			player->_state = Player::STATE::LEFT_DASH;
			
		}
		// 右方向ダッシュ移動
		else if (player->_lfAnalogDeg > ANALOG_REG_OTHER && player->_lfAnalogDeg < ANALOG_REG_FOR) {
			player->_state = Player::STATE::RIGHT_DASH;
			
		}
		// 後方向ダッシュ移動
		else if (player->_lfAnalogDeg >= -ANALOG_REG_OTHER && player->_lfAnalogDeg <= ANALOG_REG_OTHER && length >= ANALOG_MIN) {
			player->_state = Player::STATE::BACK_DASH;
		}
		// 入力がゲームパッド「RB」のみ場合は前方向ダッシュ移動
		else {
			player->_state = Player::STATE::FOR_DASH;
		}
	}
	else {
		// 通常移動速度セット
		player->_mvSpd = modeGame->_charaData->_mvSpdNorm;
		// 前方向移動
		if (player->_lfAnalogDeg >= ANALOG_REG_FOR || player->_lfAnalogDeg <= -ANALOG_REG_FOR) {
			player->_state = Player::STATE::WALK;

		}
		// 左方向移動
		else if (player->_lfAnalogDeg < -ANALOG_REG_OTHER && player->_lfAnalogDeg > -ANALOG_REG_FOR) {
			player->_state = Player::STATE::LEFT_MOVE;
		}
		// 右方向移動
		else if (player->_lfAnalogDeg > ANALOG_REG_OTHER && player->_lfAnalogDeg < ANALOG_REG_FOR) {
			player->_state = Player::STATE::RIGHT_MOVE;
		}
		// 後方向移動
		else if (player->_lfAnalogDeg >= -ANALOG_REG_OTHER && player->_lfAnalogDeg <= ANALOG_REG_OTHER) {
			player->_state = Player::STATE::BACK_MOVE;
		}
	}
}

void PlayerDash::Dash(Player* player, float nowAngle, float length) {

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // カメラの状態

	// 短押しダッシュ
	VECTOR vDash{ 0.0f,0.0f,00.f };      // ダッシュする方向
	if (trg & PAD_INPUT_6 && (player->_state != Player::STATE::JUMP) && player->_energy > modeGame->_charaData->_egDash) {
		player->_mvSpd = modeGame->_charaData->_mvSpdDash;  // ダッシュ移動速度セット
		player->_isShortDash = true;              // 短押しダッシュ移動スタート
		player->_canLongDash = true;              // 短押しダッシュ発動 ⇒ 長押しダッシュ発動可能となる
		player->_shortDashTime = SHORT_DASH_CNT;  // 短押しダッシュ移動時間をセット

	}
	if (player->_isShortDash) {
		player->_shortDashTime--;  
		if (player->_shortDashTime > 0) {
			player->_isDash = true;  // ダッシュスタート
			// キー入力があるとき入力方向にダッシュする
			if (camState != Camera::STATE::TARG_LOCK_ON) {
				player->_state = Player::STATE::FOR_DASH;
			}
			player->_isCharging = false;   // ダッシュ中溜め行動不可
			// キー入力がないとき向いている方向に直線でダッシュする
			if (length < ANALOG_MIN) {
				if (camState == Camera::STATE::TARG_LOCK_ON) {
					LeftAnalogDeg(player, length);
					vDash.x = -cos(player->_bsAngle) * player->_mvSpd;
					vDash.z = -sin(player->_bsAngle) * player->_mvSpd;
				}
				else {
					vDash.x = cos(nowAngle) * player->_mvSpd;
					vDash.z = sin(nowAngle) * player->_mvSpd;
				}
				player->_vPos.x += vDash.x;
				player->_vPos.z += vDash.z;
			}
		}
		else {
			player->_shortDashTime = 0;
			player->_isShortDash = false;
			player->_isDash = false;
		}
	}
	// 長押しダッシュ
	if (key & PAD_INPUT_6) {
		//プレイヤーが地上にいる 、長押しダッシュ可能(短押しダッシュを行った時)、短押しダッシュ移動が終わっている、エネルギー0よりある
		if (player->_canJump && player->_canLongDash && !player->_isShortDash && player->_energy > 0) {
			player->_isDash = true;       // ダッシュ状態にする
			player->_isCharging = false;  // ダッシュ中溜め行動不可
			// キー入力があるときが入力方向にダッシュする
			if (camState != Camera::STATE::TARG_LOCK_ON) {
				player->_state = Player::STATE::FOR_DASH;
			}
			// キー入力がないとき：向いている方向に直線でダッシュする
			if (length < ANALOG_MIN) {
				if (camState == Camera::STATE::TARG_LOCK_ON) {
					LeftAnalogDeg(player, length);
					vDash.x = -cos(player->_bsAngle) * player->_mvSpd;
					vDash.z = -sin(player->_bsAngle) * player->_mvSpd;
					player->_vPos.x += vDash.x;
					player->_vPos.z += vDash.z;
				}
				else {
					vDash.x = cos(nowAngle) * player->_mvSpd;
					vDash.z = sin(nowAngle) * player->_mvSpd;
					player->_vPos.x += vDash.x;
					player->_vPos.z += vDash.z;
				}
			}
		}
	}
	else {
		player->_isDash = false;
		player->_canLongDash = false;
	}
}