/**
 * @file   PlayerStatus.cpp
 * @brief  プレイヤーステータスUI描画処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Player.h"
#include "PlayerStatus.h"
#include "../Mode/ModeGame.h"

PlayerStatus::PlayerStatus() {

	_cgName        = ResourceServer::LoadGraph("res/ui/player/player_name.png");
	_cgFrame       = ResourceServer::LoadGraph("res/ui/player/player_status.png");
	_cgFrameBg     = ResourceServer::LoadGraph("res/ui/player/player_status_2.png");
	_cgBarHP       = ResourceServer::LoadGraph("res/ui/player/player_hp.png");
	_cgBarEnergy   = ResourceServer::LoadGraph("res/ui/player/player_energy.png");
}

PlayerStatus::~PlayerStatus() {
	// 何もしない
}

/*
 * フレーム処理：描画
 */
void PlayerStatus::Render() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// プレイヤー情報取得
	int hitpoint  = Player::GetInstance()->GetHitPoint();
	int energy    = Player::GetInstance()->GetEnergy();

	DrawGraph(STATUS_FRAME_POS, STATUS_FRAME_POS, _cgFrameBg, TRUE);

	DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_L + (HP_BAR_SIZE * hitpoint / modeGame->_charaData->_maxHP), HP_POS_Y_R, _cgBarHP, TRUE);
	DrawExtendGraph(ENERGY_POS_X_L, ENERGY_POS_Y_L, ENERGY_POS_X_L + (ENERGY_BAR_SIZE * energy / modeGame->_charaData->_maxEnergy), ENERGY_POS_Y_R, _cgBarEnergy, TRUE);
	DrawGraph(STATUS_FRAME_POS, STATUS_FRAME_POS, _cgFrame, TRUE);
	DrawGraph(NAME_POS_X, NAME_POS_Y, _cgName, TRUE);
}