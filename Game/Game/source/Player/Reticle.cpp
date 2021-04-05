/**
 * @file   Reticle.cpp
 * @brief  プレイヤー照準処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Reticle.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

Reticle::Reticle(){

	_cg = ResourceServer::LoadGraph("res/ui/player/mls_reticle.png");

	Initialize();
}

Reticle::~Reticle(){
    // BGMの再生周波数をデフォルトに戻す
	SetFrequencySoundMem(-1, gSound._bgm["boss"]);
}

/*
 * 初期化
 */
void Reticle::Initialize(){

	// 画面の真ん中に画像を配置
	_scrnPos.x = static_cast<float>(ApplicationMain::GetInstance()->DispSizeW() / 2 - 50);
	_scrnPos.y = static_cast<float>(ApplicationMain::GetInstance()->DispSizeH() / 2 - 50);

	_mvSpd = 16.0f;

	_hitX = _hitY = 20.0f;
	_hitW = _hitH = 80.0f;

	// 照準発生＝MLS発動中はBGMの再生周波数を小さくする(スロー再生にする)
	SetFrequencySoundMem(23000, gSound._bgm["boss"]);
}

/*
 * フレーム処理：計算
 */
void Reticle::Process(){

	// カメラの状態取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// 画面サイズ取得
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	
	// 左アナログスティック座標
	float lx, ly;   
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// 左アナログスティックを倒したときの最小値
	float analogMin = 0.3f;

	// 移動方向を決める
	float length = sqrt(lx * lx + ly * ly);;
	float rad = atan2(ly, lx);
	VECTOR vec = { 0.0f,0.0f,0.0f };

	// 移動処理
	if (length < ANALOG_MIN) {
		length = 0.0f;
	}
	else {
		length = _mvSpd;;
	}

	// vecをrad分回転させる
	vec.x = cos(rad) * length;
	vec.y = sin(rad) * length;

	// vecの分移動
	_scrnPos = VAdd(_scrnPos, vec);

	// 画面外に画像が出るのを防止
	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + 100.0f > dispSizeW) { _scrnPos.x = static_cast<float>(dispSizeW - 100); }
	if (_scrnPos.y < 0.0f) { _scrnPos.y = 0.0f; }
	if (_scrnPos.y + 100.0f > dispSizeH) { _scrnPos.y = static_cast<float>(dispSizeH - 100); }

	// カメラの状態がマルチロックオンシステムではなくなる
	if (camState != Camera::STATE::MLS_LOCK){
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * フレーム処理：描画
 */
void Reticle::Render(){

	DrawGraph(static_cast<int>(_scrnPos.x), static_cast<int>(_scrnPos.y), _cg, TRUE);
}