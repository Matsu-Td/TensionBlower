/**
 * @file   PlayerDash.h
 * @brief  プレイヤーダッシュ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

class PlayerDash {
public:
	PlayerDash();
	~PlayerDash();

	/**
     * @brief カメラロック中の移動、ダッシュモーション切替処理／
     * @brief 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
	 * @param player プレイヤークラスオブジェクトのポインタ
     * @param length  := sqrt(lx * lx + ly * ly) 左アナログスティックの入力値
	 * @param inputRT ゲームパッド「RT」入力値
     */
	void LeftAnalogDeg(Player* player, float length, float inputRT);

	/**
	 * @brief ダッシュ処理
	 * @param player プレイヤークラスオブジェクトのポインタ
	 * @param nowAngle プレイヤーが向いている方向(角度)
	 * @param length  := sqrt(lx * lx + ly * ly) 左アナログスティックの入力値
	 * @param inputRT ゲームパッド「RT」入力値
	 */
	void Dash(Player* player, float nowAngle, float length, float inputRT);

	/**
	 * @brief
	 * @param player
	 * @param inputRT
	 * @param shotMotion
	 * @param moveMotion
	 */
	void MoveAndShotChange(Player* player, float inputRT, Player::STATE shotMotion, Player::STATE moveMotion);

private:
    static constexpr int SHORT_DASH_CNT   = 10;   // 短押しダッシュ移動時間
	static constexpr int ANALOG_REG_FOR   = 120;  // 左アナログスティックを倒す前方向判定の角度範囲(ターゲットロック中のみ使用)
	static constexpr int ANALOG_REG_OTHER = 45;   // 左アナログスティックを倒す前方向以外の角度範囲(ターゲットロック中のみ使用)
	
};