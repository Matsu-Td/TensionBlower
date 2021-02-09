
/**
 * @file  ModeGameClear.cpp
 * @brief ゲームクリア画面
 * 
 * @data 2021-02-08
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeResult.h"

/**
 * 初期化
 */
bool ModeGameClear::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/仮素材/ゲームクリア.png");

	// クリアするまでの経過時間を格納
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;

	return true;
}

/**
 * 解放
 */
bool ModeGameClear::Terminate(){
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGameClear::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ゲームパッド「B」ボタンでゲームクリアモードとゲームモードを削除し、
	// リザルトモード追加
	if (trg & PAD_INPUT_2) {  
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeResult* modeResult = new ModeResult();
		ModeServer::GetInstance()->Add(modeResult, 1, "result");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGameClear::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}