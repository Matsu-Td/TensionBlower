
/**
 * @file  ModeRanking.cpp
 * @brief ランキング画面
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeRanking.h"

/**
 * 初期化
 */
bool ModeRanking::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * 解放
 */
bool ModeRanking::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeRanking::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「A」ボタンでランキングモードを削除し、タイトルモード追加
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeRanking::Render() {
	base::Render();

	// 仮実装
	DrawString(0, 0, "ランキング画面", GetColor(255, 255, 255));

	return true;
}
