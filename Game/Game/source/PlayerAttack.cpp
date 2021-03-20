/**
 * @file   PlayerAttack.cpp
 * @brief  プレイヤー近接攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "PlayerAttack.h"
#include "Sound.h"
#include "PlayerVoice.h"

PlayerAttack::PlayerAttack() {

}

/**
 * 攻撃発生時の声データを再生する
 */
void PlayerAttack::PlayAttackVoice(std::string voiceName) {
	PlaySoundMem(gPlayerVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/**
 * 現在発生中の近接攻撃ダメージ量をセットする
 */
void PlayerAttack::SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm) {

	player->_nowDmgHP = dmgHP;
	player->_nowDmgSld = dmgSld;
	player->_nowDmgNorm = dmgNorm;
}

/**
 * 近接攻撃のダメージ量を近接攻撃の種類によって切替
 */
void PlayerAttack::SwitchAttackDamage(Player* player) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	switch (player->_state) {
	case Player::STATE::WEAK_ATCK1:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP1, CHARA_DATA->_wkDmgSld1, CHARA_DATA->_wkDmg1);
		break;
	case Player::STATE::WEAK_ATCK2:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP2, CHARA_DATA->_wkDmgSld2, CHARA_DATA->_wkDmg2);
		break;
	case Player::STATE::WEAK_ATCK3:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP3, CHARA_DATA->_wkDmgSld3, CHARA_DATA->_wkDmg3);
		break;
	case Player::STATE::WEAK_ATCK4:
		SetAttackDamage(player, CHARA_DATA->_wkDmgHP4, CHARA_DATA->_wkDmgSld4, CHARA_DATA->_wkDmg4);
		break;
	case Player::STATE::STRG_ATCK1:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP1, CHARA_DATA->_stDmgSld1, CHARA_DATA->_stDmg1);
		break;
	case Player::STATE::STRG_ATCK2:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP2, CHARA_DATA->_stDmgSld2, CHARA_DATA->_stDmg2);
		break;
	case Player::STATE::STRG_ATCK3:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP3, CHARA_DATA->_stDmgSld3, CHARA_DATA->_stDmg3);
		break;
	case Player::STATE::STRG_ATCK4:
		SetAttackDamage(player, CHARA_DATA->_stDmgHP4, CHARA_DATA->_stDmgSld4, CHARA_DATA->_stDmg4);
		break;
	}
}

/**
 * 強近接攻撃への派生関連処理
 */
void PlayerAttack::NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName) {

	if (player->_energy < attackEnergy) {                      // エネルギー残量チェック
		return;
	}
	PlaySoundMem(gSound._se["h_attack"], DX_PLAYTYPE_BACK);
	player->_state = std::move(nextState);                     // 次の攻撃の状態へ遷移
	player->_energy -= std::move(attackEnergy);                // エネルギー消費
	player->_canAutoCharge = false;                            // 強近接攻撃時はエネルギー自動回復停止
	player->_autoChargeCnt = Player::AUTO_CHARGE_CNT;          // 溜め復帰時間セット
	player->_attackCnt = player->_attackTotalTime[attackName]; // 攻撃モーション時間セット
	player->_receptionTime = RECEPTION_TIME;                   // 次攻撃受付時間セット
	player->_hitFlag = false;                                  // ボスに攻撃が当たっていない
	SwitchAttackDamage(player);                                // 現在の近接攻撃のボスへのダメージ量をセット
}

/**
 * 弱近接攻撃への派生関連処理
 */
void PlayerAttack::NextWeakAttack(Player* player, Player::STATE nextState, std::string attackName) {

	PlaySoundMem(gSound._se["l_attack"], DX_PLAYTYPE_BACK);
	player->_state = std::move(nextState);                     // 次の攻撃の状態へ遷移
	player->_attackCnt = player->_attackTotalTime[attackName]; // 攻撃モーション時間セット
	player->_receptionTime = RECEPTION_TIME;				   // 次攻撃受付時間セット
	player->_hitFlag = false;                                  // ボスに攻撃が当たっていない
	SwitchAttackDamage(player);                                // 現在の近接攻撃のボスへのダメージ量をセット
}


void PlayerAttack::AttackAction(Player* player) {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// 攻撃カウント
	if (player->_attackCnt <= 0) {
		player->_attackCnt = 0;
		player->_hitFlag = false;
	}
	else {
		player->_attackCnt--;
	}

	// 攻撃受付時間
	if (player->_attackCnt <= 20) {
		player->_receptionTime--;
	}
	if (player->_receptionTime <= 0) {
		player->_receptionTime = 0;
		player->_attackReloadTime = ATTACK_RELOAD_TIME;
		player->_isAttack = false;
	}


	// 近接攻撃切替
	switch (player->_state) {
	case Player::STATE::WEAK_ATCK1:
		if (player->_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃2へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayAttackVoice("strong");
				NextStrongAttack(player,CHARA_DATA->_egAtck2, Player::STATE::STRG_ATCK2, "slash_h");
			}
			// 弱近接攻撃2へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃2の声データ再生
				PlayAttackVoice("weak2");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK2, "slash_l");

			}
		}
		break;
	case Player::STATE::WEAK_ATCK2:
		if (player->_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃3へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayAttackVoice("strong");
				NextStrongAttack(player, CHARA_DATA->_egAtck3, Player::STATE::STRG_ATCK3, "slash_h");
			}
			// 弱近接攻撃3へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃3の声データ再生
				PlayAttackVoice("weak3");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK3, "slash_l");
			}
		}
		break;
	case Player::STATE::WEAK_ATCK3:
		if (player->_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃4へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayAttackVoice("strong");
				NextStrongAttack(player, CHARA_DATA->_egAtck4, Player::STATE::STRG_ATCK4, "slash_h");
			}
			// 弱近接攻撃4へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃4の声データ再生
				PlayAttackVoice("weak4");
				NextWeakAttack(player, Player::STATE::WEAK_ATCK4, "slash_l");
			}
		}
		break;
		// 攻撃派生終了（弱攻撃4,強攻撃1～4）
	case Player::STATE::WEAK_ATCK4:
	case Player::STATE::STRG_ATCK1:
	case Player::STATE::STRG_ATCK2:
	case Player::STATE::STRG_ATCK3:
	case Player::STATE::STRG_ATCK4:
		if (player->_attackCnt <= 0) {
			player->_canHitFlag = false;
			player->_isAttack = false;               // 近接攻撃終了
			player->_attackReloadTime = ATTACK_RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	}

	// 近接攻撃当たり判定発生
	if (!player->_hitFlag) {
		if (player->_attackCnt >= 20 && player->_attackCnt < 35) {
			player->_canHitFlag = true;
		}
		else {
			player->_canHitFlag = false;
		}
	}
}

/**
 * 近接攻撃処理(初手のみ)
 */
void PlayerAttack::FirstAttack(Player* player) {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_vPos.y == 0.0f && player->_attackReloadTime == 0) {
		if (trg & PAD_INPUT_2 && !player->_isAttack) {
			// 弱近接攻撃1の声データ再生
			PlayAttackVoice("weak1");

			player->_isAttack = true;
			NextWeakAttack(player, Player::STATE::WEAK_ATCK1, "slash_l");

		}
		if (trg & PAD_INPUT_4 && !player->_isAttack) {
			// 強近接攻撃の声データ再生
			PlayAttackVoice("strong");

			player->_isAttack = true;
			NextStrongAttack(player, CHARA_DATA->_egAtck1, Player::STATE::STRG_ATCK1, "slash_h");
		}
	}
}

/**
 * 近接攻撃処理(2発目以降)
 */
void PlayerAttack::SecondAttack(Player* player) {
	
	if (player->_isAttack) {
		AttackAction(player);
	}
	if (player->_attackReloadTime > 0) {
		player->_attackReloadTime--;
	}
}