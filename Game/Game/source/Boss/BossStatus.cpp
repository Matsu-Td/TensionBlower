/**
 * @file   BossStatus.cpp
 * @brief  ボスステータスUI描画
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Boss.h"
#include "BossStatus.h"
#include "../Mode/ModeGame.h"

BossStatus::BossStatus() {

	_cgName    = ResourceServer::LoadGraph("res/ui/boss/enemy_name.png");
	_cgFrame   = ResourceServer::LoadGraph("res/ui/boss/enemy_status.png");
	_cgFrameBg = ResourceServer::LoadGraph("res/ui/boss/enemy_status_2.png");
	_cgShield  = ResourceServer::LoadGraph("res/ui/boss/enemy_shield.png");

	// HPバーと本数表示用のアイコン読み込み
	for (int i = 0; i < HP_BAR_NUM; i++) {
		_cgHP[i] = ResourceServer::LoadGraph(_hpBarString[i]);
		_cgIcon[i] = ResourceServer::LoadGraph(_iconString[i]);
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

	// ステータスバー背景
	DrawGraph(FRAME_POS_X, FRAME_BG_POS_Y, _cgFrameBg, TRUE);

	// 5重のHPバーをフェーズ毎に制御する
	int nowBarNum = HP_BAR_NUM - 1 - phase;  // 現在の残りHPバー本数-1
	for (int i = 0; i < nowBarNum; i++) {
		DrawExtendGraph(HP_POS_X_L, HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[i], TRUE);
	}
	// 一番上に表示するHPバー
	DrawExtendGraph(HP_POS_X_L + HP_SIZE - (HP_SIZE * (hitpoint - (HP_ONE * nowBarNum)) / HP_ONE),
		            HP_POS_Y_L, HP_POS_X_R, HP_POS_Y_R, _cgHP[nowBarNum], TRUE);

	// HPバー残り本数表示
	if (hitpoint > 0) {
		for (int i = 0; i < HP_BAR_NUM - phase; i++) {
			DrawGraph(ICON_POS_X[i], ICON_POS_Y, _cgIcon[i], TRUE);
		}
	}

	// シールドバー
	DrawExtendGraph(SHIELD_POS_X_L + SHIELD_SIZE - (SHIELD_SIZE * shield / SHIELD_ONE), SHIELD_POS_Y_L, SHIELD_POS_X_R, SHIELD_POS_Y_R, _cgShield, TRUE);

	// ステータスバー本体
	DrawGraph(FRAME_POS_X, FRAME_POS_Y, _cgFrame, TRUE);

	// ボス名表示
	DrawGraph(NAME_POS_X, NAME_POS_Y, _cgName, TRUE);
}