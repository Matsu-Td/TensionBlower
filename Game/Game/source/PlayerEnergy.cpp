/**
 * @file   PlayerEnergy.cpp
 * @brief  プレイヤーエネルギー関係処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerEnergy.h"

PlayerEnergy::PlayerEnergy() {

}

/**
 * エネルギー消費処理
 */
void PlayerEnergy::CostEnergy(Player* player, float costEnergy) {
	player->_canAutoCharge = false;
	player->_autoChargeCnt = Player::AUTO_CHARGE_CNT;
	player->_energy -= costEnergy;
}

/**
 * エネルギー管理
 */
void PlayerEnergy::EnergyManager(Player* player, Player::STATE oldState) {

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float addEne;

	if (player->_energy > 0 || player->_energy < CHARA_DATA->_maxEnergy) {
		if (player->_swCharge) {               // デバッグ用
			if (oldState != player->_state) {
				// ジャンプ(消費)
				if (player->_state == Player::STATE::JUMP) {
					CostEnergy(player, CHARA_DATA->_egJump);
				}
				// 短押しダッシュ(消費)
				if (player->_isShortDash) {
					CostEnergy(player, CHARA_DATA->_egDash);
				}
			}

			// 長押しダッシュ(消費)
			if (!player->_isShortDash && player->_isDash) {
				CostEnergy(player, 1);
			}

			// マルチロックオンシステム(消費)
			if (camState == Camera::STATE::MLS_LOCK) {
				CostEnergy(player, CHARA_DATA->_egMLS);
			}

			// ボス付近で行動する(回復)
			if (player->_isNearBoss) {
				addEne = CHARA_DATA->_egAutoXArea;
			}
			else {
				addEne = 1.0f;
			}

			if (player->_energy >= CHARA_DATA->_maxEnergy) {
				return;
			}

			//　溜め(回復)
			if (player->_isCharging) {
				player->_energy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
			}

			// 自動回復開始のインターバル
			if (!player->_canAutoCharge) {
				player->_autoChargeCnt--;
				if (player->_autoChargeCnt <= 0) {   // 一定の自動回復開始間隔を設ける
					player->_autoChargeCnt = 0;
					player->_canAutoCharge = true;
				}
			}
			// 自動回復(回復)
			else if (!player->_isCharging) {
				player->_energy += CHARA_DATA->_egAutoRec * addEne;
				gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * addEne;
			}
		}
	}

	// MLSによる弾き返しでシールド破壊した場合、[ボスの弾の数 * 指定のエネルギー量]分回復する
	if (Boss::GetInstance()->_mlsDownFlag) {
		player->_energy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	//最小エネルギー値オーバー防止
	if (player->_energy < 0) {
		player->_energy = 0;
	}
	// 最大エネルギー値オーバー防止
	if (player->_energy > CHARA_DATA->_maxEnergy) { 
		player->_energy = CHARA_DATA->_maxEnergy;
	}
}