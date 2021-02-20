#pragma once

/**
 * @file  PlayerJump.h
 * @brief プレイヤージャンプ処理
 *
 * @date 2021-02-19
 */

#include "appframe.h"
#include "Player.h"

class PlayerJump {
public:
	/**
	 * ジャンプ処理
	 * @param player プレイヤークラスオブジェクトのポインタ
	 */
	void JumpAction(Player* player);

private:
	static constexpr float IN_VEL = 4.0f;      // 初速
	static constexpr float MULT_HALF = 0.5f;   // 1/2乗算
	static constexpr float JUMP_CNT = 0.2f;    // ジャンプ時間
};
