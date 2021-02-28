/**
 * @file   ModeResult.cpp
 * @brief  リザルト画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeResult.h"

/**
 * 初期化
 */
bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/result.png");
	SetFontSize(64);
	_score = 0;

	return true;
}

/**
 * 解放
 */
bool ModeResult::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeResult::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッド「B」ボタンでリザルトモードを削除し、タイトルモード追加
	if (trg & PAD_INPUT_2) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeResult::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

#if 1  // 仮実装
	int x = 800;
	int y = 90;
	int size = 200;
	int color = GetColor(0, 0, 0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, 0, "スコア計算未実装", GetColor(255, 255, 255)); 
	DrawFormatString(x, y, color, "%4d 秒", gGlobal._gameTime / 1000); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._remainingHP); y += size;
	DrawFormatString(x, y, color, "%4d 回", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalGetEnergy); y += size;
	DrawFormatString(x, y, color, "%4d", _score);

#endif

	return true;
}