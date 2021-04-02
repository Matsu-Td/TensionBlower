/**
 * @file   PlayerJump.h
 * @brief  プレイヤージャンプ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

/**
 * プレイヤージャンプ処理
 */
class PlayerJump {
public:
	/**
	 * @brief ジャンプ処理
	 * @param player プレイヤークラスオブジェクトのポインタ
	 */
	void JumpAction(Player* player);

private:
	static constexpr float IN_VEL = 5.0f;      // 初速
	static constexpr float MULT_HALF = 0.5f;   // 1/2乗算
	static constexpr float JUMP_CNT = 0.2f;    // ジャンプ時間
	static constexpr float GRAVITY = 0.9f; // 重力加速度値
};
