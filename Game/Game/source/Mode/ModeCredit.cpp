/**
 * @file   ModeCredit.cpp
 * @brief  クレジットモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"
#include "../Sound/Sound.h"

/**
 * 初期化
 */
bool ModeCredit::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/credit.png");

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
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
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
	
	DrawGraph(0, 0, _cg, FALSE);

	return true;
}
