/**
 * @file   ModeGame.cpp
 * @brief  ゲーム本体
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "Sound.h"
#include <memory>

/**
 * 初期化
 */
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	PlaySoundMem(gSound._bgm["boss"], DX_PLAYTYPE_LOOP);

	// JSONファイルからキャラデータ読み込み
	_charaData = std::make_unique<CharaData>("res/json/", "CharaData");

	// オブジェクトサーバーに登録
	_objServer.Add(NEW Stage()); 
	_objServer.Add(NEW Player()); 
	_objServer.Add(NEW Boss());

	// グローバル変数初期化(リザルト画面、スコア計算用)
	gGlobal._remainingHP = 0;
	gGlobal._totalRepelCnt = 0;
	gGlobal._totalGetEnergy = 0;

	// ゲームスタート表示
	ModeServer::GetInstance()->Add(NEW ModeGameStart, 2, "start");
	_objServer.Process();
	_stopObjProcess = true;

	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.164f, 0.164f, 0.164f, 0.0f));

	int Light0Handle = CreateDirLightHandle(VGet(0.062f, -0.479f, 0.875f));
	SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light0Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light1Handle = CreateDirLightHandle(VGet(-0.878f, 0.479f, 0.000f));
	SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light2Handle = CreateDirLightHandle(VGet(0.878f, 0.479f, 0.000f));
	SetLightDifColorHandle(Light2Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light2Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light2Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light3Handle = CreateDirLightHandle(VGet(0.062f, 0.479f, -0.875f));
	SetLightDifColorHandle(Light3Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light3Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light3Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//// ライトの設定
	//SetLightEnable(FALSE);
	//SetGlobalAmbientLight(GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//int Light0Handle = CreatePointLightHandle(VGet(-125.000f, 100.000f, 0.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light0Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light1Handle = CreatePointLightHandle(VGet(125.000f, 100.000f, 0.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 0.000f));
	//SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light2Handle = CreatePointLightHandle(VGet(0.000f, 100.000f, -125.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light2Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light2Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light2Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light3Handle = CreatePointLightHandle(VGet(0.000f, 100.000f, 125.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light3Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light3Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light3Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	return true;
}

/**
 * 解放
 */
bool ModeGame::Terminate() {
	base::Terminate();

	// ライトハンドル削除
	DeleteLightHandleAll();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	
	if (_stopObjProcess == false) {
		_objServer.Process();
	}
	_cam.Process();

    // Effekseerにより再生中のエフェクトを更新
	UpdateEffekseer3D();

	// ゲームパッド「START」ボタンでポーズモード追加
	if (trg & PAD_INPUT_8) { 
		ModePause* modePause = NEW ModePause();
		ModeServer::GetInstance()->Add(modePause, 99, "pause");
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeGame::Render() {
	base::Render();
	
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);	
	
	_objServer.Render();

	_cam.Render();
	_playerStatus.Render();
	_bossStatus.Render();

	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}

