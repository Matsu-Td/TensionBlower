/**
 * @file   Energy.cpp
 * @brief  プレイヤーエネルギー関係処理
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "../Mode/ModeGame.h"
#include "Player.h"

using namespace tensionblower::player;

/*
 * エネルギー消費処理
 */
void Player::CostEnergy(int costEnergy) {

	_canAutoCharge = false;
	_autoChargeCnt = Player::AUTO_CHARGE_CNT;
	_energy -= costEnergy;
}

/*
 * ボスとの距離を確認(自動回復用)
 */
void Player::CheckDistanceToBoss() {

	// ボス位置情報取得
	VECTOR bsPos = boss::Boss::GetInstance()->GetPos();
	float sx = _vPos.x - bsPos.x;
	float sz = _vPos.z - bsPos.z;
	float length = Util::Sqrt(sx, sz);

	_bsAngle = atan2(sz, sx);

	// ボスとの距離が50m以下かどうか
	if (length <= 50) {
		_isNearBoss = true;
	}
	else {
		_isNearBoss = false;
	}
}

/*
 * エネルギーの回復、消費処理
 */
void Player::EnergyManager() {

	// カメラの状態取得
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();
	
	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	// ボスとの距離を確認
	CheckDistanceToBoss();

	if (_energy > 0 || _energy < modeGame->_charaData->_maxEnergy) {
		int addEne;

		if (_oldState != _state) {
			// ジャンプ(消費)
			if (_state == Player::STATE::JUMP) {
				CostEnergy(modeGame->_charaData->_egJump);
			}
			// 短押しダッシュ(消費)
			if (_isShortDash) {
				CostEnergy(modeGame->_charaData->_egDash);
			}
		}

		// 長押しダッシュ(消費)
		if (!_isShortDash && _isDash) {
			CostEnergy(1);
		}

		// マルチロックオンシステム(消費)
		if (camState == camera::Camera::STATE::MLS_LOCK) {
			CostEnergy(modeGame->_charaData->_egMLS);
		}

		// ボス付近で行動する(回復)
		if (_isNearBoss) {
			addEne = modeGame->_charaData->_egAutoXArea;
		}
		else {
			addEne = 1;
		}

		if (_energy >= modeGame->_charaData->_maxEnergy) {
			return;
		}

		//　溜め(回復)
		if (_isCharging) {
			_energy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * modeGame->_charaData->_egAutoXChrg * addEne;
		}

		// 自動回復開始のインターバル
		if (!_canAutoCharge) {
			_autoChargeCnt--;
			if (_autoChargeCnt <= 0) {   // 一定の自動回復開始間隔を設ける
				_autoChargeCnt = 0;
				_canAutoCharge = true;
			}
		}
		// 自動回復(回復)
		else if (!_isCharging) {
			_energy += modeGame->_charaData->_egAutoRec * addEne;
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAutoRec * addEne;
		}

	}

	// MLSによる弾き返しでシールド破壊した場合、[ボスの弾の数 * 指定のエネルギー量]分回復する
	if (boss::Boss::GetInstance()->_mlsDownFlag) {
		_energy += (modeGame->_charaData->_egShotNum * boss::Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (modeGame->_charaData->_egShotNum * boss::Boss::GetInstance()->_bulletNum);
	}

	//最小エネルギー値オーバー防止
	if (_energy < 0) {
		_energy = 0;
	}
	// 最大エネルギー値オーバー防止
	if (_energy > modeGame->_charaData->_maxEnergy) {
		_energy = modeGame->_charaData->_maxEnergy;
	}
}