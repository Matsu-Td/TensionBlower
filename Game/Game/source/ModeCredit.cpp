
/**
 * @file  ModeCredit.cpp
 * @brief クレジット画面
 *
 * @date 2021-02-09
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"

/**
 * 初期化
 */
bool ModeCredit::Initialize() {
	if (!base::Initialize()) { return false; }

//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * 解放
 */
bool ModeCredit::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeCredit::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「A」ボタンでクレジットモードを削除しタイトルモード追加
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeCredit::Render() {
	base::Render();
	
	// 仮実装
	DrawString(0, 0, "クレジット画面", GetColor(255, 255, 255));

	return true;
}
