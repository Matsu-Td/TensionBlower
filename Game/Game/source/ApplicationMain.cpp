/**
 * @file   ApplicationMain.cpp
 * @brief  アプリケーションメイン
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Sound.h"
#include "PlayerVoice.h"
#include "BossVoice.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeAmgLogo.h"
#include "ModeTeamLogo.h"

// 実体
ApplicationMain	g_oApplicationMain;

/**
 * 初期化
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// グローバル変数の初期化
	gGlobal.Init();
	gSound.Init();
	gPlayerVoice.Init();
	gBossVoice.Init();

	// モードの登録
	ModeServer::GetInstance()->Add(NEW ModeAmgLogo(), 1, "amglogo");

	return true;
}

/**
 * 解放
 */
bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}

/**
 * フレーム処理：入力
 */
bool ApplicationMain::Input() {
	base::Input();
	return true;
}

/**
 * フレーム処理：計算
 */
bool ApplicationMain::Process() {
	base::Process();
	return true;
}

/**
 * フレーム処理：描画
 */
bool ApplicationMain::Render() {
	base::Render();
	return true;
}

