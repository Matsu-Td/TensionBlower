
/**
 * @file  ModeGameOver.cpp
 * @brief ゲームオーバー画面
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"

/**
 * 初期化
 */
bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/仮素材/ゲームオーバー.png");

	return true;
}

/**
 * 解放
 */
bool ModeGameOver::Terminate(){
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGameOver::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ゲームパッド「B」ボタンでゲームオーバーモードとゲームモードを削除し、
	// タイトルモードを追加
	if (trg & PAD_INPUT_2) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeTitle* modeTitle = new ModeTitle();
		ModeServer::GetInstance()->Add(modeTitle, 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGameOver::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}