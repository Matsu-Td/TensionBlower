/**
 * @file   PlayerAttack.h
 * @brief  プレイヤー近接攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/25
 */

#pragma once

#include "Player.h"

/**
 * @brief プレイヤー近接攻撃処理
 */
class PlayerAttack{
public:
	/**
	 * @brief 近接攻撃のダメージ量を近接攻撃の種類によって切替
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 */
	void SwitchAttackDamage(Player* player);

	/**
     * @brief 現在発生中の近接攻撃ダメージ量をセットする
	 * @param player  プレイヤークラスオブジェクトのポインタ
     * @param dmgHP   シールド状態のボスのヒットポイントに与えるダメージ量
     * @param dmgSld  シールド状態のボスのシールドに与えるダメージ量
     * @param dmgNorm シールドがない状態のボスのヒットポイントに与えるダメージ量
     */
	void SetAttackDamage(Player* player, int dmgHP, int dmgSld, int dmgNorm);

	/**
     * @brief 強近接攻撃への派生関連処理
     * @param player  プレイヤークラスオブジェクトのポインタ
     * @param attackEnergy 指定された強近接攻撃での消費エネルギー量
     * @param nextState    派生する強近接攻撃の種類
     * @param attackName   派生する強近接攻撃の名前(攻撃モーション時間セット用)
     */
	void NextStrongAttack(Player* player,int attackEnergy, Player::STATE nextState, std::string attackName);

	/**
	 * @brief 弱近接攻撃への派生関連処理
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 * @param nextState    派生する弱近接攻撃の種類
	 * @param attackName   派生する弱近接攻撃の名前(攻撃モーション時間セット用)
	 */
	void NextWeakAttack(Player* player, Player:: STATE nextState, std::string attackName);
	
	/**
	 * @brief 各近接攻撃へのキー入力処理
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 */
	void AttackAction(Player* player);

	/**
     * @brief 近接攻撃処理(初手のみ)
	 * @param player  プレイヤークラスオブジェクトのポインタ
     */
	void FirstAttack(Player* player);

	/**
     * @brief 近接攻撃処理(2発目以降)
	 * @param player  プレイヤークラスオブジェクトのポインタ
     */
	void SecondAttack(Player* player);

	/**
	 * @brief 攻撃発生時の声データを再生する
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 * @param voiceName 再生する声データの名前
	 */
	void PlayAttackVoice(std::string voiceName);

	/**
	 * @brief 弱近接攻撃のヒット判定時間を設定する
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 */
	void SetWeakHitTime(Player* player);

	/**
	 * @brief 強近接攻撃のヒット判定時間を設定する
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 */
	void SetStrongHitTime(Player* player);

	static constexpr int RECEPTION_TIME = 30;      // 次近接攻撃受付時間
	static constexpr int ATTACK_RELOAD_TIME = 90;  // 近接・射撃攻撃リロード時間
};