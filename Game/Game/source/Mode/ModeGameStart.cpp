/**
 * @file   ModeGameStart.cpp
 * @brief  MISSION START文字表示
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "../Player/PlayerVoice.h"

/**
 * 初期化
 */
bool ModeGameStart::Initialize() {
	if (!base::Initialize()) { return false; }

	// クリア時の声データ再生
	PlaySoundMem(gPlayerVoice._vc["gamestart"], DX_PLAYTYPE_BACK);

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/missionstart.png");

	return true;
}

/**
 * 解放
 */
bool ModeGameStart::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGameStart::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (trg & PAD_INPUT_2) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_stopObjProcess = false;
		// 「MISSION START」 表示が消えてからクリアタイムカウントスタート
		gGlobal._gameTime = GetNowCount();
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGameStart::Render() {
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}
