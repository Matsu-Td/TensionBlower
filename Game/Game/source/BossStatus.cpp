
/**
 * @file  BossStatus.cpp
 * @brief ボスステータスUI描画
 *
 * @date 2021-02-25
 */

#include "Boss.h"
#include "BossStatus.h"
#include "ModeGame.h"

BossStatus::BossStatus() {

	_cgName    = ResourceServer::LoadGraph("res/ui/boss/enemy_name.png");
	_cgFrame   = ResourceServer::LoadGraph("res/ui/boss/enemy_status.png");
	_cgFrameBg = ResourceServer::LoadGraph("res/ui/boss/enemy_status_2.png");
	_cgShield  = ResourceServer::LoadGraph("res/ui/boss/enemy_shield.png");
	for (int i = 0; i < HP_BAR_NUM; i++) {
		_cgHP[i] = ResourceServer::LoadGraph(_cgString[i]);
	}
}

BossStatus::~BossStatus() {

}

/**
 * フレーム処理：描画
 */
void BossStatus::Render(){

	// ボス情報取得
	int hitpoint = Boss::GetInstance()->GetHitPoint();
	int shield   = Boss::GetInstance()->GetShield();
	int phase    = Boss::GetInstance()->GetPhase();

	DrawGraph(FRAME_POS_X, FRAME_POS_Y, _cgFrameBg, TRUE);

	// 5重のHPバーをフェーズ毎に制御する
	if (phase == 0) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[0], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[1], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[2], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[3], TRUE);
		DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - 4000) / HP_ONE), HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[4], TRUE);
	}
	if (phase == 1) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[0], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[1], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[2], TRUE);
		DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - 3000) / HP_ONE), HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[3], TRUE);
	}
	if (phase == 2) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[0], TRUE);
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[1], TRUE);
		DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - 2000) / HP_ONE), HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[2], TRUE);
	}
	if (phase == 3) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[0], TRUE);
		DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - HP_ONE) / HP_ONE), HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[1], TRUE);
	}
	if (phase == 4) {
		DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * hitpoint / HP_ONE), HP_POS_Y_L, HP_POS_X_R, 80, _cgHP[0], TRUE);
	}

	DrawExtendGraph(SHIELD_POS_X_L + SHIELD_SIZE - (SHIELD_SIZE * shield / SHIELD_ONE), SHIELD_POS_Y_L, SHIELD_POS_X_R, SHIELD_POS_Y_R, _cgShield, TRUE);
	DrawGraph(FRAME_POS_X, FRAME_POS_Y, _cgFrame, TRUE);
	DrawGraph(NAME_POS_X, NAME_POS_Y, _cgName, TRUE);
}