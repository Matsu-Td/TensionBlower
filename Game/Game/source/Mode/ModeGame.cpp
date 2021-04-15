/**
 * @file   ModeGame.cpp
 * @brief  ゲームモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "../Sound/Sound.h"

using namespace tensionblower::mode;

/*
 * 初期化
 */
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	PlaySoundMem(gSound._bgm["boss"], DX_PLAYTYPE_LOOP);

	// JSONファイルからキャラデータ読み込み
	_charaData = std::make_unique<charadata::CharaData>("res/json/", "CharaData");

	// オブジェクトサーバーに登録
	_objServer.Add(NEW stage::Stage()); 
	_objServer.Add(NEW player::Player()); 
	_objServer.Add(NEW boss::Boss());
	
	// グローバル変数初期化(リザルト画面、スコア計算用)
	gGlobal._remainingHP = 0;
	gGlobal._totalRepelCnt = 0;
	gGlobal._totalGetEnergy = 0;

	// ゲームスタート表示
	::mode::ModeServer::GetInstance()->Add(NEW ModeGameStart, 2, "start");
	_objServer.Process();
	_stopObjProcess = true;

	// ライトの設定
	SetLight();

	return true;
}

/*
 * 解放
 */
bool ModeGame::Terminate() {
	base::Terminate();

	_objServer.Clear();

	// ライトハンドル削除
	DeleteLightHandleAll();

	return true;
}

/*
 * ライトの設定
 */
void ModeGame::SetLight() {

	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.164f, 0.164f, 0.164f, 0.0f));

	int Light0Handle = CreateDirLightHandle(VGet(0.062f, -0.479f, 0.875f));
	SetLightColorHandle(Light0Handle);

	int Light1Handle = CreateDirLightHandle(VGet(-0.878f, 0.479f, 0.000f));
	SetLightColorHandle(Light1Handle);

	int Light2Handle = CreateDirLightHandle(VGet(0.878f, 0.479f, 0.000f));
	SetLightColorHandle(Light2Handle);

	int Light3Handle = CreateDirLightHandle(VGet(0.062f, 0.479f, -0.875f));
	SetLightColorHandle(Light3Handle);
}

/*
 * ライトのディフューズカラーを設定する
 */
void ModeGame::SetLightColorHandle(int lightHandle) {
	SetLightDifColorHandle(lightHandle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(lightHandle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(lightHandle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));
}

/*
 * フレーム処理：計算
 */
bool ModeGame::Process() {
	base::Process();

	// キーのトリガ情報取得
	int trg = ApplicationMain::GetInstance()->GetKeyTrg();
	
	// オブジェクトの処理停止要否
	if (_stopObjProcess == false) {
		_objServer.Process();
	}
	_cam.Process();

    // Effekseerにより再生中のエフェクトを更新
	UpdateEffekseer3D();

	// ゲームパッド「START」ボタンでポーズモード追加
	if (trg & PAD_INPUT_8) { 
		ModePause* modePause = NEW ModePause();
		::mode::ModeServer::GetInstance()->Add(modePause, 99, "pause");
	}

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModeGame::Render() {
	base::Render();
	
	// 3D描画設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);	

	// オブジェクトの描画
	_objServer.Render();

	// カメラ情報の描画
	_cam.Render();

	// インゲームのUI描画
	_playerStatus.Render();
	_bossStatus.Render();

	// エフェクシアデータの再生、描画
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}

