/**
 * @file   ModeGameOver.cpp
 * @brief  ゲームオーバーモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"

using namespace tensionblower::mode;

/*
 * 初期化
 */
bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	// ボスステージのBGM再生停止
	StopSoundMem(gSound._bgm["boss"]);
	// ゲームオーバー音再生
	PlaySoundMem(gSound._se["lose"], DX_PLAYTYPE_BACK);
	// ゲームオーバー時の声データ再生
	PlaySoundMem(gPlayerVoice._vc["gameover"], DX_PLAYTYPE_BACK);

	_cg[0] = resource::ResourceServer::LoadGraph("res/band.png");
	_cg[1] = resource::ResourceServer::LoadGraph("res/gameover.png");

	return true;
}

/*
 * 解放
 */
bool ModeGameOver::Terminate(){
	base::Terminate();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModeGameOver::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	::mode::ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ゲームパッド「B」ボタンでゲームオーバーモードとゲームモードを削除し、
	// タイトルモードを追加
	if (trg & PAD_INPUT_2) {
		StopSoundMem(gSound._se["lose"]);

		::mode::ModeServer::GetInstance()->Del(this);
		::mode::ModeServer::GetInstance()->Del(::mode::ModeServer::GetInstance()->Get("game"));

		::mode::ModeServer::GetInstance()->Add(NEW ModeTitle, 1, "title");
	}

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModeGameOver::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}