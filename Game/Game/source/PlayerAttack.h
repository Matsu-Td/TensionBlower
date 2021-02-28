/**
 * @file   PlayerAttack.h
 * @brief  プレイヤー近接攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/25
 */

#pragma once

#include "Player.h"

class PlayerAttack{
	friend Player;
public:
	PlayerAttack();
	~PlayerAttack();

	/**
	 * @brief 初期化.
	 * 
	 */
	void Initialize();

	/**
	 * 近接攻撃のダメージ量を近接攻撃の種類によって切替
	 */
	void SwitchAttackDamage(Player* player);

	/**
     * 現在発生中の近接攻撃ダメージ量をセットする
	 * @param player プレイヤークラスオブジェクトのポインタ
     * @param dmgHP   シールド状態のボスのヒットポイントに与えるダメージ量
     * @param dmgSld  シールド状態のボスのシールドに与えるダメージ量
     * @param dmgNorm シールドがない状態のボスのヒットポイントに与えるダメージ量
     */
	void SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm);

	/**
     * 強近接攻撃への派生関連処理
     * @param attackEnergy 指定された強近接攻撃での消費エネルギー量
     * @param nextState    派生する強近接攻撃の種類
     * @param attackName   派生する強近接攻撃の名前(攻撃モーション時間セット用)
     */
	void NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName);

	/**
	 * 弱近接攻撃への派生関連処理
	 * @param nextState    派生する弱近接攻撃の種類
	 * @param attackName   派生する弱近接攻撃の名前(攻撃モーション時間セット用)
	 */
	void NextWeakAttack(Player* player, Player:: STATE nextState, std::string attackName);
	
	/**
	 * 各近接攻撃へのキー入力処理
	 */
	void AttackAction(Player* player);

	/**
     * 近接攻撃処理(初手のみ)
     */
	void FirstAttack(Player* player);

	/**
     * 近接攻撃処理(2発目以降)
     */
	void SecondAttack(Player* player);

	static constexpr int RECEPTION_TIME = 30;   // 次近接攻撃受付時間
	static constexpr int ATTACK_RELOAD_TIME = 90;   // 近接・射撃攻撃リロード時間
};