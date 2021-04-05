/**
 * @file  ApplicationBase.cpp
 * @brief アプリケーション基底クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_pInstance = nullptr;


ApplicationBase::ApplicationBase() {
	_pInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

/*
 * 初期化
 */
bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DXライブラリの初期化
	if(AppWindowed()){
		// ウィンドウモード(TRUE)かフルスクリーンモード(FALSE)を指定
		ChangeWindowMode(FALSE);		
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1){	
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// Effekseerを初期化する
	// 引数には画面に表示する最大パーティクル数を設定する
	if (Effekseer_Init(100000) == -1){
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	// Effekseerを使用する場合は必ず設定する
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する
	// ただし、DirectX11を使用する場合は実行する必要はない
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = std::make_unique<ModeServer>();
	
	return true;
}

/*
 * 解放
 */
bool ApplicationBase::Terminate() {
	// Effekseerを終了
	Effkseer_End();
	// DXライブラリ開放
	DxLib_End();

	return true;
}

/*
 * フレーム処理：入力
 */
bool ApplicationBase::Input() {

	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// キーのトリガ情報生成

	return true;
}

/*
 * フレーム処理：計算
 */
bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();

	return true;
}

/*
 * フレーム処理：描画
 */
bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();

	return true;
}
