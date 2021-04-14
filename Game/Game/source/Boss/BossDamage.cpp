/** 
 * @file   BossDamage.cpp
 * @brief  ボスが受けるダメージ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

using namespace tensionblower;

  /*
   * プレイヤーに弾き返された弾によるダメージ処理
   */
void Boss::RepelDamage() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));

	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// シールドがあるとき
	if (_shield > 0) {
		_hitpoint -= modeGame->_charaData->_repelDmgHP;
		_shield -= modeGame->_charaData->_repelDmgSld;

		if (_shield <= 0) {
			_shield = 0;
			_mlsDownFlag = true;  // プレイヤーに弾き返された弾でシールドが破壊されるとtrue
		}
	}
	// シールドがないとき
	else {
		_hitpoint -= modeGame->_charaData->_repelDmg;
	}
}

/*
 * プレイヤーから受けたダメージ量計算
 */
void Boss::AttackDamage() {

	// ダウン状態時のみ被弾時の声データ再生
	if (_state == Boss::STATE::DOWN) {
		PlayVoice("hidan");
	}
	// ヒット音再生
	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);

	// ダメージ量格納
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();

	// シールドがあるとき
	if (_shield > 0) {
		_hitpoint -= dmgHP;
		_shield -= dmgSld;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
	// シールドがないとき
	else {
		_hitpoint -= dmgNorm;
	}
}

/*
 * ヒットポイントへの爆発ダメージ
 */
void Boss::ExplosionDamageHP() {
	// シールドがあるとき
	if (_shield > 0) {
		_hitpoint -= EXPLOSION_DMG_HP;
	}
	// シールドがないとき
	else {
		_hitpoint -= EXPLOSION_DMG_NORM;
	}
}

/*
 * シールドへの爆発ダメージ
 */
void Boss::ExplosionDamageShield() {
	// シールドがあるとき
	if (_shield > 0) {
		_shield -= EXPLOSION_DMG_SLD;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
}
