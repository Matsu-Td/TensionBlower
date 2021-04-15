/**
 * @file   ApplicationMain.cpp
 * @brief  プロジェクトのメイン処理
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "appFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"
#include "../Boss/LoadBossVoice.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/ModeGame.h"
#include "../Mode/ModeAmgLogo.h"
#include "../Mode/ModeTeamLogo.h"

using namespace tensionblower;

// 実体
ApplicationMain	g_oApplicationMain;

/*
 * 初期化
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// グローバル変数の初期化
	gGlobal.Initialize();
	gSound.Initialize();
	gPlayerVoice.Initialize();
	gBossVoice.Initialize();

	// モードの登録
	::mode::ModeServer::GetInstance()->Add(NEW mode::ModeAmgLogo(), 1, "amglogo");

	return true;
}

/*
 * 解放
 */
bool ApplicationMain::Terminate() {
	base::Terminate();

	return true;
}

/*
 * フレーム処理：入力
 */
bool ApplicationMain::Input() {
	base::Input();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ApplicationMain::Process() {
	base::Process();

	return true;
}

/*
 * フレーム処理：描画
 */
bool ApplicationMain::Render() {
	base::Render();

	return true;
}

