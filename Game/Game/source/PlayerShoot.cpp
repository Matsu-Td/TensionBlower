/**
 * @file   PlayerShoot.cpp
 * @brief  プレイヤー射撃攻撃
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerShoot.h"

/**
 * 射撃攻撃 (ゲームパッド「RT」で射撃)
 */
void PlayerShoot::ShootingAttack(Player* player) {

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	// ゲームパッド「RT」
	int rt = dinput.Z;
	// RT最小値
	int rtMin = -100;

	if (rt < rtMin && !player->_isCharging && !player->_isZeroShot) { // 溜め状態及び装弾数がゼロになった場合は射撃不可
		if (player->_bulletNum == 0) {
			// 弾を打ち切ってしまうとフラグが立つ(= true) ⇒ 射撃不可
			player->_isZeroShot = true;
		}
		if (player->_bulletNum > 0) {
			if (player->_canShot) {
				player->_state = Player::STATE::SHOT_ATCK;
				player->_isShooting = true;
				player->_playTime = 30.0f;
				player->_reloadTime = Player::RELOAD_TIME;	   // リロード開始時間をセット
				player->_canShot = false;
				player->_bulletNum--;
				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				PlayerBullet* bullet = NEW PlayerBullet();
				float angle = atan2(player->_vDir.z, player->_vDir.x);
				VECTOR tmp = player->_vPos;
				tmp.y = player->_vPos.y + 7.0f;
				bullet->SetPos(tmp);
				bullet->SetShotAngle(angle);
				modeGame->_objServer.Add(bullet);  // 弾発生、射撃開始
			}
			else {
				player->_shotInterval--;
				if (player->_shotInterval == 0) {
					player->_canShot = true;
					player->_shotInterval = 10;      // 一定の射撃間隔を設ける
				}
			}
		}
	}
	else {
		// 射撃を行わなければリロード開始
		player->_isShooting = false;
		player->_reloadTime--;
		// 弾を打ち切った場合は即時リロード開始
		if (player->_isZeroShot) {
			if (player->_bulletNum < Player::MAX_BULLET) {
				player->_bulletNum++;
			}
		}
		// 弾が残っている状態かつリロード開始時間ゼロでリロード開始
		else if (player->_reloadTime <= 0) {
			if (player->_bulletNum < Player::MAX_BULLET) {
				player->_bulletNum++;
			}
		}
	}
	// リロード完了で_shotZeroFlag解除(= false)
	if (player->_bulletNum == Player::MAX_BULLET) {
		player->_isZeroShot = false;
	}
}