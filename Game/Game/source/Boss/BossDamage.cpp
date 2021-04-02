/**
 * @file   BossDamage.cpp
 * @brief　ボスが受けるダメージ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "BossDamage.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

 /**
  * プレイヤーに弾き返された弾によるダメージ処理
  */
void BossDamage::RepelDamage(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// シールドがあるとき
	if (boss->_shield > 0) {
		boss->_hitpoint -= modeGame->_charaData->_repelDmgHP;
		boss->_shield -= modeGame->_charaData->_repelDmgSld;

		if (boss->_shield <= 0) {
			boss->_shield = 0;
			boss->_mlsDownFlag = true;  // プレイヤーに弾き返された弾でシールドが破壊されるとtrue
		}
	}
	// シールドがないとき
	else {
		boss->_hitpoint -= modeGame->_charaData->_repelDmg;
	}
}

/**
 * プレイヤーから受けたダメージ量計算
 */
void BossDamage::AttackDamage(Boss* boss) {

	// ダウン状態時のみ被弾時の声データ再生
	if (boss->_state == Boss::STATE::DOWN) {
		boss->PlayVoice("hidan");
	}
	// ヒット音再生
	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);

	// ダメージ量格納
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();
	// シールドがあるとき
	if (boss->_shield > 0) {
		boss->_hitpoint -= dmgHP;
		boss->_shield -= dmgSld;
		if (boss->_shield <= 0) {
			boss->_shield = 0;
		}
	}
	// シールドがないとき
	else {
		boss->_hitpoint -= dmgNorm;
	}
}

/**
 * ヒットポイントへの爆発ダメージ
 */
void BossDamage::ExplosionDamageHP(Boss* boss) {
	// シールドがあるとき
	if (boss->_shield > 0) {
		boss->_hitpoint -= EXPLOSION_DMG_HP;
	}
	// シールドがないとき
	else {
		boss->_hitpoint -= EXPLOSION_DMG_NORM;
	}
}

/**
 * シールドへの爆発ダメージ
 */
void BossDamage::ExplosionDamageShield(Boss* boss) {
	// シールドがあるとき
	if (boss->_shield > 0) {
		boss->_shield -= EXPLOSION_DMG_SLD;
		if (boss->_shield <= 0) {
			boss->_shield = 0;
		}
	}
}
