
/**
 * @file  ModeGame.cpp
 * @brief ゲーム本体
 *
 * @date 2021-02-08
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

	PlaySoundMem(gSound._bgm["boss"], DX_PLAYTYPE_BACK);

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
//	SetUseLighting(FALSE);
//	SetLightEnable(true);
//	_shadowMapHandle = MakeShadowMap(2028, 2028);

//	SetLightDirection(VGet(0.0f, -0.5f, 0.0f));
//	SetShadowMapLightDirection(_shadowMapHandle, VGet(0.0f, -0.5f, 0.0f));
//	SetShadowMapDrawArea(_shadowMapHandle, VGet(-124.0f, -1.0f, -124.0f), VGet(124.0f, 250.0f, 124.0f));

	ModeServer::GetInstance()->Add(NEW ModeGameStart, 2, "start");

	return true;
}

/**
 * 解放
 */
bool ModeGame::Terminate() {
	base::Terminate();

	// オブジェクトサーバーのコンテナに登録していた要素を全て削除、メモリ解放
	_objServer.Clear();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	_cam.Process();
	_objServer.Process();

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

//	ShadowMap_DrawSetup(_shadowMapHandle);
	
	
	_objServer.Render();
//	ShadowMap_DrawEnd();

//	SetUseShadowMap(0, _shadowMapHandle);
//	_objServer.Render();
//	SetUseShadowMap(0, -1);
	_cam.Render();
	_playerStatus.Render();

	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}

