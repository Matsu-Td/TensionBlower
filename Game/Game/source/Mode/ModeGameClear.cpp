/**
 * @file   ModeGameClear.cpp
 * @brief  ゲームクリアモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/01/26
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeResult.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"

using namespace tensionblower::mode;

/*
 * 初期化
 */
bool ModeGameClear::Initialize(){
	if (!base::Initialize()) { return false; }

	// ボスステージのBGM再生停止
	StopSoundMem(gSound._bgm["boss"]);
	// クリア音再生
	PlaySoundMem(gSound._se["win"], DX_PLAYTYPE_BACK);
	// クリア時の声データ再生
	PlaySoundMem(gPlayerVoice._vc["clear"], DX_PLAYTYPE_BACK);

	_cg[0] = resource::ResourceServer::LoadGraph("res/band.png");
	_cg[1] = resource::ResourceServer::LoadGraph("res/missionclear.png");

	// クリアするまでの経過時間を格納
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;

	return true;
}

/*
 * 解放
 */
bool ModeGameClear::Terminate(){
	base::Terminate();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModeGameClear::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetKeyTrg();

	::mode::ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ゲームパッド「B」ボタンでゲームクリアモードとゲームモードを削除し、
	// リザルトモード追加
	if (trg & PAD_INPUT_2) {  
		StopSoundMem(gSound._se["win"]);

		::mode::ModeServer::GetInstance()->Del(this);
		::mode::ModeServer::GetInstance()->Del(::mode::ModeServer::GetInstance()->Get("game"));

		::mode::ModeServer::GetInstance()->Add(NEW ModeResult(), 1, "result");
	}

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModeGameClear::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}