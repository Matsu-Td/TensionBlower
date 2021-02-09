
/**
 * @file  ModeTutorial.cpp
 * @brief チュートリアル画面
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"

/**
 * 初期化
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * 解放
 */
bool ModeTutorial::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeTutorial::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「A」ボタンでチュートリアルモードを削除し、
	// タイトルモード追加
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeTutorial::Render() {
	base::Render();

	// 仮実装
	DrawString(0, 0, "チュートリアル画面", GetColor(255, 255, 255));

	return true;
}
