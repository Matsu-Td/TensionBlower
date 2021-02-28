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

	// ゲームスタート表示
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
	
	_objServer.Render();

	_cam.Render();
	_playerStatus.Render();
	_bossStatus.Render();

	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}

