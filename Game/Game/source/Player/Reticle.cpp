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

using namespace tensionblower::player;

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
void Reticle::Initialize() {

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
 * 移動処理
 */
void Reticle::Move() {

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
}

/*
 * 画像が画面外に出るのを防止
 */
void Reticle::PreventOffScreen() {

	// 画面サイズ取得
	int dispSizeW = ApplicationMain::GetInstance()->DispSizeW();
	int dispSizeH = ApplicationMain::GetInstance()->DispSizeH();

	// 画像のサイズを取得
	int graphSizeX, graphSizeY;
	GetGraphSize(_cg, &graphSizeX, &graphSizeY);

	if (_scrnPos.x < 0) { _scrnPos.x = 0; }
	if (_scrnPos.x + graphSizeX > dispSizeW) { _scrnPos.x = static_cast<float>(dispSizeW - graphSizeX); }
	if (_scrnPos.y < 0.0f) { _scrnPos.y = 0.0f; }
	if (_scrnPos.y + graphSizeY > dispSizeH) { _scrnPos.y = static_cast<float>(dispSizeH - graphSizeY); }

}

/*
 * 削除処理
 */
void Reticle::Deletion() {
	// カメラの状態取得
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();

	// カメラの状態がマルチロックオンシステムではなくなる
	if (camState != camera::Camera::STATE::MLS_LOCK) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * フレーム処理：計算
 */
void Reticle::Process(){

	// 移動処理
	Move();

	// 画面外に画像が出るのを防止
	PreventOffScreen();

	// 削除処理
	Deletion();
}

/*
 * フレーム処理：描画
 */
void Reticle::Render(){

	DrawGraph(static_cast<int>(_scrnPos.x), static_cast<int>(_scrnPos.y), _cg, TRUE);
}