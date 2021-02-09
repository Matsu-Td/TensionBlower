
/**
 * @file  ModePlugin.cpp
 * @brief プラグイン画面
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModePlugin.h"

/**
 * 初期化
 */
bool ModePlugin::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * 解放
 */
bool ModePlugin::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModePlugin::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「B」ボタンでプラグインモード削除し、ゲームモード追加
	if (trg & PAD_INPUT_2) {   
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "game");
	}
	// ゲームパッド「A」ボタンでプラグインモード削除し、タイトルモード追加
	if (trg & PAD_INPUT_1) {  
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModePlugin::Render() {
	base::Render();

	DrawString(0, 0, "プラグイン画面", GetColor(255, 255, 255));

	return true;
}
