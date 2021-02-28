/**
 * @file   ModeGameOver.cpp
 * @brief  ゲームオーバー画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "Sound.h"

/**
 * 初期化
 */
bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	// ボスステージのBGM再生停止
	StopSoundMem(gSound._bgm["boss"]);

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/gameover.png");

	return true;
}

/**
 * 解放
 */
bool ModeGameOver::Terminate(){
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGameOver::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ゲームパッド「B」ボタンでゲームオーバーモードとゲームモードを削除し、
	// タイトルモードを追加
	if (trg & PAD_INPUT_2) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeServer::GetInstance()->Add(NEW ModeTitle, 1, "title");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGameOver::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}