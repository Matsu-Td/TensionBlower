/**
 * @file   PlayerMotion.h
 * @brief  プレイヤーモーション切替
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "Player.h"

class PlayerMotion {
public:
	PlayerMotion();

	/**
	 * プレイヤーモーション切替
	 * @param player プレイヤークラスオブジェクトのポインタ
	 * @param oldState プレイヤーの処理前の状態
	 */
	void SwitchMotion(Player* player, Player::STATE oldState);
};