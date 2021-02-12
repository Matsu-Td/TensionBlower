
/**
 * @file  ApplicationMain.cpp
 * @brief アプリケーションメイン
 *
 * @date 2021-02-08
 */


#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"

// 実体
ApplicationMain	g_oApplicationMain;

/**
 * 初期化
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// アプリケーショングローバルの初期化
	gGlobal.Init();

	// モードの登録
	ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");

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

