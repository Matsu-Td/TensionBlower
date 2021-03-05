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
#include "Sound.h"

/**
 * 初期化
 */
bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/result.png");

	_allScore = 0;
	_timeScore = MAX_SCORE;
	_hpScore = MAX_SCORE;
	_repelScore = 0;
	_energyScore = 0;

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
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	// スコア計算：経過時間
	int timepoint = gGlobal._gameTime / MMSEC2SEC - 120;  // 120以上時間経過でスコア減点
	if (timepoint > 0) {
		_timeScore = MAX_SCORE - timepoint * 200;
	}

	// スコア計算：残り体力
	_hpScore = gGlobal._remainingHP * 100;

	// スコア計算：合計弾き回数
	_repelScore = gGlobal._totalRepelCnt * 3000;

	// スコア計算：総獲得エネルギー量
	_energyScore = gGlobal._totalGetEnergy * 5;

	//// スコア計算：総スコア
	_allScore = _timeScore + _hpScore + _repelScore + _energyScore;

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
	SetFontSize(64);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawFormatString(x, y, color, "%4d", gGlobal._gameTime / MMSEC2SEC); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._remainingHP); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(x, y, color, "%4d", gGlobal._totalGetEnergy); y += size;
	SetFontSize(80);
	x = 1500;
	y = 100;
	DrawFormatString(x, y, color, "%6d", _timeScore); y += size;
	DrawFormatString(x, y, color, "%6d", _hpScore); y += size;
	DrawFormatString(x, y, color, "%6d", _repelScore); y += size;
	DrawFormatString(x, y, color, "%6d", _energyScore); y += size;
	DrawFormatString(x, y, color, "%6d", _allScore);

#endif

	return true;
}