#pragma once

/**
 * @file  PlayerMotion.h
 * @brief プレイヤーモーション切替
 *
 * @date 2021-02-13
 */

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