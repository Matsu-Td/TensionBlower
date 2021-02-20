
/**
 * @file  PlayerJump.cpp
 * @brief プレイヤージャンプ処理
 *
 * @date 2021-02-19
 */

#include "ApplicationMain.h"
#include "PlayerJump.h"
#include "ModeGame.h"

/**
 * ジャンプ処理
 */
void PlayerJump::JumpAction(Player* player) {
	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (player->_energy >= CHARA_DATA->_egJump) {
		if (trg & PAD_INPUT_1 && player->_canJump && !player->_isCharging) {
			player->_state = Player::STATE::JUMP;
			player->_canJump = false;
			player->_mvSpd = CHARA_DATA->_mvSpdNorm;
			player->_jumpTime = 0.0f;
		}
	}
	if (!player->_canJump) {
		player->_vPos.y = IN_VEL * player->_jumpTime - MULT_HALF * Player::GRAVITY * player->_jumpTime * player->_jumpTime;
	}

	player->_jumpTime += JUMP_CNT;

	if (player->_vPos.y < Player::GROUND_Y) {
		player->_vPos.y = Player::GROUND_Y;
		if (player->_isCharging == false) {
			player->_canJump = true;
		}
	}
}