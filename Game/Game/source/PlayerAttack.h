#pragma once

/**
 * @file  PlayerAttack.h
 * @brief プレイヤー近接攻撃処理
 *
 * @date 2021-02-10
 */

#include "Player.h"

class PlayerAttack{
	friend Player;
public:
	PlayerAttack();
	~PlayerAttack();

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
	int a = 0;
	// 近接攻撃関連
//	bool _attackFlag;      // 攻撃発生フラグ(攻撃発動中)
//	int _attackCnt;        // 攻撃遷移、終了カウント(攻撃モーション総再生時間を代入)
//	int _attackReloadTime; // 近接攻撃用リロード時間(リロード中は近接攻撃不可)
//	int _receptionTime;    // 次の近接攻撃遷移受付時間
//	int _canHitFlag;       // 近接攻撃当たり判定可否(true:可能, false:不可)
//	std::unordered_map<std::string, int> _attackTotalTime;  // 各攻撃モーションの総再生時間を格納する

//	static constexpr int ATTACK_NUM = 8;  // 近接攻撃の種類の数
//	std::string AttackName[ATTACK_NUM] =  // 各近接攻撃の名前を格納
//	{ "weak_atck1" ,"weak_atck2" ,"weak_atck3" ,"weak_atck4", 
//	  "strg_atck1", "strg_atck2", "strg_atck3", "strg_atck4" };
	static constexpr int RECEPTION_TIME = 30;   // 次近接攻撃受付時間
	static constexpr int ATTACK_RELOAD_TIME = 90;   // 近接・射撃攻撃リロード時間
};