
/**
 * @file  ModeGame.cpp
 * @brief ゲーム本体
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include <memory>

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	//SetBackgroundColor(0, 255, 255);
	_charaData = std::make_unique<CharaData>("res/json/", "CharaData");

	// オブジェクトサーバーに登録
	_objServer.Add(NEW Stage());
	_objServer.Add(NEW Player());
	_objServer.Add(NEW Boss());

	// グローバル変数初期化(リザルト画面、スコア計算用)
	gGlobal._gameTime = GetNowCount();
	gGlobal._remainingHP = 0;
	gGlobal._totalRepelCnt = 0;
	gGlobal._totalGetEnergy = 0;

//	_shadowMapHandle = MakeShadowMap(2028, 2028);
	SetLightDirection(VGet(0.0f, -0.5f, 0.0f));
//	SetShadowMapLightDirection(_shadowMapHandle, VGet(0.0f, -0.5f, 0.0f));
//	SetShadowMapDrawArea(_shadowMapHandle, VGet(-124.0f, -1.0f, -124.0f), VGet(124.0f, 250.0f, 124.0f));
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	_objServer.Clear(); 

	return true;
}

bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

		_cam.Process();
		_objServer.Process();

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer3D();

	if (trg & PAD_INPUT_8) {
		ModeOption* modeOption = NEW ModeOption();
		ModeServer::GetInstance()->Add(modeOption, 99, "option");
	}

	return true;
}

bool ModeGame::Render() {
	base::Render();
	
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

//	ShadowMap_DrawSetup(_shadowMapHandle);
	
	
	_objServer.Render();
//	ShadowMap_DrawEnd();

//	SetUseShadowMap(0, _shadowMapHandle);
//	_objServer.Render();
//	SetUseShadowMap(0, -1);
	_cam.Render();

	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}

