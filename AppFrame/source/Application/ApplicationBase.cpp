/**
 * @file  ApplicationBase.cpp
 * @brief アプリケーション基底クラス
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "ApplicationBase.h"

using namespace appframe;

ApplicationBase	*ApplicationBase::_pInstance = nullptr;


ApplicationBase::ApplicationBase() :_key(0), _keyTrg(0), _dInput({0}) {
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

	// Effekseer初期化
	if (Effekseer_Init(8000) == -1){
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = std::make_unique<mode::ModeServer>();
	
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

	int keyold = _key;
	
	_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_keyTrg = (_key ^ keyold) & _key;	// キーのトリガ情報生成
	GetJoypadDirectInputState(DX_INPUT_PAD1, &_dInput);

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
