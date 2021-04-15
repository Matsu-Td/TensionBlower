/**
 * @file   Attack.cpp
 * @brief  プレイヤー近接攻撃処理
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"
#include "../Sound/Sound.h"

using namespace tensionblower::player;

/*
 * 現在発生中の近接攻撃ダメージ量をセットする
 */
void Player::SetAttackDamage(int dmgHP, int dmgSld, int dmgNorm) {

	_nowDmgHP = dmgHP;
	_nowDmgSld = dmgSld;
	_nowDmgNorm = dmgNorm;
}

/*
 * 近接攻撃のダメージ量を近接攻撃の種類によって切替
 */
void Player::SwitchAttackDamage() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	switch (_state) {
	case Player::STATE::WEAK_ATCK1:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP1, modeGame->_charaData->_wkDmgSld1, modeGame->_charaData->_wkDmg1);
		break;
	case Player::STATE::WEAK_ATCK2:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP2, modeGame->_charaData->_wkDmgSld2, modeGame->_charaData->_wkDmg2);
		break;
	case Player::STATE::WEAK_ATCK3:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP3, modeGame->_charaData->_wkDmgSld3, modeGame->_charaData->_wkDmg3);
		break;
	case Player::STATE::WEAK_ATCK4:
		SetAttackDamage(modeGame->_charaData->_wkDmgHP4, modeGame->_charaData->_wkDmgSld4, modeGame->_charaData->_wkDmg4);
		break;
	case Player::STATE::STRG_ATCK1:
		SetAttackDamage(modeGame->_charaData->_stDmgHP1, modeGame->_charaData->_stDmgSld1, modeGame->_charaData->_stDmg1);
		break;
	case Player::STATE::STRG_ATCK2:
		SetAttackDamage(modeGame->_charaData->_stDmgHP2, modeGame->_charaData->_stDmgSld2, modeGame->_charaData->_stDmg2);
		break;
	case Player::STATE::STRG_ATCK3:
		SetAttackDamage(modeGame->_charaData->_stDmgHP3, modeGame->_charaData->_stDmgSld3, modeGame->_charaData->_stDmg3);
		break;
	case Player::STATE::STRG_ATCK4:
		SetAttackDamage(modeGame->_charaData->_stDmgHP4, modeGame->_charaData->_stDmgSld4, modeGame->_charaData->_stDmg4);
		break;
	}
}

/*
 * 強近接攻撃への派生関連処理
 */
void Player::NextStrongAttack(int attackEnergy, STATE nextState, std::string attackName) {

	if (_energy < attackEnergy) {                      // エネルギー残量チェック
		return;
	}

	PlaySoundMem(gSound._se["h_attack"], DX_PLAYTYPE_BACK);

	_state = std::move(nextState);                  // 次の攻撃の状態へ遷移
	_energy -= std::move(attackEnergy);             // エネルギー消費
	_canAutoCharge = false;                         // 強近接攻撃時はエネルギー自動回復停止
	_autoChargeCnt = Player::AUTO_CHARGE_CNT;       // 溜め復帰時間セット
	_attackCnt = _mapAttackTotalTime[attackName];   // 攻撃モーション時間セット
	_receptionTime = RECEPTION_TIME;                // 次攻撃受付時間セット
	_hitFlag = false;                               // ボスに攻撃が当たっていない

	SwitchAttackDamage();                           // 現在の近接攻撃のボスへのダメージ量をセット
}

/*
 * 弱近接攻撃への派生関連処理
 */
void Player::NextWeakAttack(STATE nextState, std::string attackName) {

	PlaySoundMem(gSound._se["l_attack"], DX_PLAYTYPE_BACK);

	_state = std::move(nextState);                  // 次の攻撃の状態へ遷移
	_attackCnt = _mapAttackTotalTime[attackName];   // 攻撃モーション時間セット
	_receptionTime = RECEPTION_TIME;			    // 次攻撃受付時間セット
	_hitFlag = false;                               // ボスに攻撃が当たっていない

	SwitchAttackDamage();                           // 現在の近接攻撃のボスへのダメージ量をセット
}

/*
 * 各近接攻撃へのキー入力処理
 */
void Player::AttackAction() {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();
	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));

	// 攻撃カウント
	if (_attackCnt <= 0) {
		_attackCnt = 0;
		_hitFlag = false;
	}
	else {
		_attackCnt--;
	}

	// 攻撃受付時間
	if (_attackCnt <= 20) {
		_receptionTime--;
	}
	if (_receptionTime <= 0) {
		_receptionTime = 0;
		_attackReloadTime = ATTACK_RELOAD_TIME;
		_isAttack = false;
	}


	// 近接攻撃切替
	switch (_state) {
	case Player::STATE::WEAK_ATCK1:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃2へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck2, Player::STATE::STRG_ATCK2, "slash_h");
				SetStrongHitTime();
			}
			// 弱近接攻撃2へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃2の声データ再生
				PlayVoice("weak2");

				NextWeakAttack(STATE::WEAK_ATCK2, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
	case Player::STATE::WEAK_ATCK2:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃3へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck3, Player::STATE::STRG_ATCK3, "slash_h");
				SetStrongHitTime();
			}
			// 弱近接攻撃3へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃3の声データ再生
				PlayVoice("weak3");

				NextWeakAttack(STATE::WEAK_ATCK3, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
	case Player::STATE::WEAK_ATCK3:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃4へ派生
			if (trg & PAD_INPUT_4) {
				// 強近接攻撃の声データ再生
				PlayVoice("strong");

				NextStrongAttack(modeGame->_charaData->_egAtck4, Player::STATE::STRG_ATCK4, "slash_h");
				SetStrongHitTime();
			}
			// 弱近接攻撃4へ派生
			else if (trg & PAD_INPUT_B) {
				// 弱近接攻撃4の声データ再生
				PlayVoice("weak4");

				NextWeakAttack(STATE::WEAK_ATCK4, "slash_l");
				SetWeakHitTime();
			}
		}
		break;
		// 攻撃派生終了（弱攻撃4,強攻撃1～4）
	case Player::STATE::WEAK_ATCK4:
	case Player::STATE::STRG_ATCK1:
	case Player::STATE::STRG_ATCK2:
	case Player::STATE::STRG_ATCK3:
	case Player::STATE::STRG_ATCK4:
		if (_attackCnt <= 0) {
			_canHitFlag = false;
			_isAttack = false;               // 近接攻撃終了
			_attackReloadTime = ATTACK_RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	}

	// 近接攻撃当たり判定発生
	if (!_hitFlag) {
		if (_attackCnt >= _hitEndCnt && _attackCnt < _hitStartCnt) {
			_canHitFlag = true;
		}
		else {
			_canHitFlag = false;
		}
	}
}

/*
 * 近接攻撃処理(初手のみ)
 */
void Player::FirstAttack() {

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	if (_vPos.y == 0.0f && _attackReloadTime == 0) {
		if (trg & PAD_INPUT_2 && !_isAttack) {
			// 弱近接攻撃1の声データ再生
			PlayVoice("weak1");

			_isAttack = true;
			NextWeakAttack(STATE::WEAK_ATCK1, "slash_l");
			SetWeakHitTime();

		}
		if (trg & PAD_INPUT_4 && !_isAttack) {
			// 強近接攻撃の声データ再生
			PlayVoice("strong");

			_isAttack = true;

			mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
		
			NextStrongAttack(modeGame->_charaData->_egAtck1, STATE::STRG_ATCK1, "slash_h");
			SetStrongHitTime();
		}
	}
}

/*
 * 近接攻撃処理(2発目以降)
 */
void Player::SecondAttack() {

	if (_isAttack) {
		AttackAction();
	}
	if (_attackReloadTime > 0) {
		_attackReloadTime--;
	}
}

/*
 * 弱近接攻撃のヒット判定時間を設定する
 */
void Player::SetWeakHitTime() {
	_hitStartCnt = 35;
	_hitEndCnt   = 20;
}

/*
 * 強近接攻撃のヒット判定時間を設定する
 */
void Player::SetStrongHitTime() {
	_hitStartCnt = 60;
	_hitEndCnt   = 50;
}
