
/**
 * @file  ModeResult.cpp
 * @brief リザルト画面
 *
 * @date 2021-02-08
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

#if 1  // 仮実装
	int y = 0;
	int size =200;
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, y, "リザルト画面", GetColor(255, 255, 255)); y += 200;
	DrawFormatString(0, y, GetColor(255, 255, 255), "経過時間           : %d秒", gGlobal._gameTime / 1000); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "残り体力           : %d", gGlobal._remainingHP); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "弾き返し回数       : %d 回", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "総獲得エネルギー量 : %d", gGlobal._totalGetEnergy); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "総スコア 　　　　　: %d", _score);

#endif

	DrawGraph(0, 0, _cg, FALSE);
	return true;
}