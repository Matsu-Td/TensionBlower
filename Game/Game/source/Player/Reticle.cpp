/**
 * @file   Reticle.cpp
 * @brief  プレイヤー照準処理
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
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

	// 画像のサイズを取得
	int graphSizeX, graphSizeY;
	GetGraphSize(_cg, &graphSizeX, &graphSizeY);

	// 画面の中心に画像を配置
	_scrnPos.x = static_cast<float>(ApplicationMain::GetInstance()->DispSizeW() / 2 - (graphSizeX / 2));
	_scrnPos.y = static_cast<float>(ApplicationMain::GetInstance()->DispSizeH() / 2 - (graphSizeY / 2));

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
	Camera::STATE camState = Camera::GetInstance()->GetState();

	// 画面サイズ取得
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();

	float lx, ly;
	Util::GetLeftStickParamXY(lx, ly);

	float rad = atan2(ly, lx);                  // 左スティックの角度(rad)
	float length = Util::GetLeftStickLength(); 	// 左スティックの移動量
	
	VECTOR vec = { 0.0f,0.0f,0.0f };

	// 移動処理
	if (length < Util::ANALOG_MIN) {
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

	// 画像のサイズを取得
	int graphSizeX, graphSizeY;
	GetGraphSize(_cg, &graphSizeX, &graphSizeY);

	// 画面外に画像が出るのを防止
	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + graphSizeX > dispSizeW) { _scrnPos.x = static_cast<float>(dispSizeW - graphSizeX); }
	if (_scrnPos.y < 0.0f) { _scrnPos.y = 0.0f; }
	if (_scrnPos.y + graphSizeY > dispSizeH) { _scrnPos.y = static_cast<float>(dispSizeH - graphSizeY); }

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