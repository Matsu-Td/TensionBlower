
/**
 * @file  ModeGameStart.cpp
 * @brief MISSION START文字表示
 *
 * @date 2021-02-14
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"

/**
 * 初期化
 */
bool ModeGameStart::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/missionstart.png");

	return true;
}

/**
 * 解放
 */
bool ModeGameStart::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGameStart::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (trg & PAD_INPUT_2) {
		// 「MISSION START」 表示が消えてからクリアタイムカウントスタート
		gGlobal._gameTime = GetNowCount();
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGameStart::Render() {
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], TRUE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}
