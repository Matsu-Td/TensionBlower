#pragma once

/**
 * @file  PlayerEnergy.h
 * @brief プレイヤーエネルギー関係処理
 *
 * @date 2021-02-14
 */

#include "appframe.h"
#include "Player.h"

class PlayerEnergy {
public:
	PlayerEnergy();
	~PlayerEnergy();

	/**
     * エネルギー消費処理
	 * @param player プレイヤークラスオブジェクトのポインタ
     * @param costEnergy エネルギー消費量
     */
	void CostEnergy(Player* player, float costEnergy);

	/**
     * エネルギー管理
	 * @param player プレイヤークラスオブジェクトのポインタ
     * @param oldState 処理前のプレイヤーの状態
     */
	void EnergyManager(Player* player, Player::STATE oldState);
};
