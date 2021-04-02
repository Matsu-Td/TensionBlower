/**
 * @file   ModeRanking.cpp
 * @brief  ランキング画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeRanking.h"
#include "../Sound/Sound.h"

/**
 * 初期化
 */
bool ModeRanking::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/ranking.png");

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
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeRanking::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}
