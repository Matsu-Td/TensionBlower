/**
 * @file   PlayerStatus.cpp
 * @brief  プレイヤーステータスUI描画
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Player.h"
#include "PlayerStatus.h"
#include "ModeGame.h"

PlayerStatus::PlayerStatus() {

	_cgName        = ResourceServer::LoadGraph("res/ui/player/player_name.png");
	_cgFrame       = ResourceServer::LoadGraph("res/ui/player/player_status.png");
	_cgFrameBg     = ResourceServer::LoadGraph("res/ui/player/player_status_2.png");
	_cgBarHP       = ResourceServer::LoadGraph("res/ui/player/player_hp.png");
	_cgBarEnergy   = ResourceServer::LoadGraph("res/ui/player/player_energy.png");
	_cgRemainFrame = ResourceServer::LoadGraph("res/ui/player/remain_frame.png");

	for (int i = 0; i < ALL_NUM; i++) {
		_cgRemainNum[i]= ResourceServer::LoadGraph(_numString[i]);
	}
}

PlayerStatus::~PlayerStatus() {

}

void PlayerStatus::Render() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// プレイヤー情報取得
	int hitpoint  = Player::GetInstance()->GetHitPoint();
	int energy    = Player::GetInstance()->GetEnergy();
	int bulletNum = Player::GetInstance()->GetBulletNum();

	DrawGraph(STATUS_FRAME_POS, STATUS_FRAME_POS, _cgFrameBg, TRUE);

	DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_L + (HP_BAR_SIZE * hitpoint / CHARA_DATA->_maxHP), HP_POS_Y_R, _cgBarHP, TRUE);
	DrawExtendGraph(ENERGY_POS_X_L, ENERGY_POS_Y_L, ENERGY_POS_X_L + (ENERGY_BAR_SIZE * energy / CHARA_DATA->_maxEnergy), ENERGY_POS_Y_R, _cgBarEnergy, TRUE);
	DrawGraph(STATUS_FRAME_POS, STATUS_FRAME_POS, _cgFrame, TRUE);
	DrawGraph(NAME_POS_X, NAME_POS_Y, _cgName, TRUE);

	DrawGraph(NUM_FRAME_POS_X, NUM_FRAME_POS_Y, _cgRemainFrame, TRUE);

	DrawGraph(NUM_POS_X1, NUM_POS_Y, _cgRemainNum[bulletNum / 100], TRUE);      // 100の位
	DrawGraph(NUM_POS_X2, NUM_POS_Y, _cgRemainNum[bulletNum / 10 % 10], TRUE);  // 10の位
	DrawGraph(NUM_POS_X3, NUM_POS_Y, _cgRemainNum[bulletNum % 10], TRUE);       // 1の位
}