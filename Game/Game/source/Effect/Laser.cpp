/**
 * @file   Laser.cpp
 * @brief  ボスのレーザー攻撃
 * 
 * @author matsuo tadahiko
 * @date   2021/02/14
 */

#include "Laser.h"
#include "../Mode/ModeGame.h"
#include "../Boss/Boss.h"

using namespace tensionblower::effect;

Laser::Laser(VECTOR pos, float radius, float angle, float roteSpd) {

	_effectHandle  = resource::ResourceServer::LoadEffekseerEffect("res/effect/beam/effect_beam.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_roteAngle = angle;
	_roteSpd = roteSpd;
	_radius = radius;

	Initialize();
}

Laser::~Laser() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * 初期化
 */
void Laser::Initialize() {

	_r = 5.0f;
	_effectCnt = 240;
	_mlsCnt = 0;
}

/*
 * 削除処理
 */
void Laser::Deletion() {

	// ボスの状態を取得
	boss::Boss::STATE bsState = boss::Boss::GetInstance()->GetState();

	// ボスがダウンしたらレーザー削除
	if (bsState == boss::Boss::STATE::DOWN) {
		StopEffekseer3DEffect(_playingHandle);

		mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
		modeGame->_objServer.Del(this);
	}

	_effectCnt--;
	// 再生カウントが「0」になればレーザーを削除する
	if (_effectCnt <= 0) {
		mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
		modeGame->_objServer.Del(this);
	}
}

/*
 * フレーム処理：計算
 */
void Laser::Process() {

	// カメラの状態を取得
	camera::Camera::STATE camState = camera::Camera::GetInstance()->GetState();

	// マルチロックオンシステム発動中の回転速度を1/100にする
	if (camState == camera::Camera::STATE::MLS_LOCK) {
		_roteAngle += _roteSpd * MLS_SPD;
	}
	else {
		_roteAngle += _roteSpd;
	}

	// 発射位置
	_vPos.x = cos(util::DegToRad(_roteAngle)) * _radius;
	_vPos.z = sin(util::DegToRad(_roteAngle)) * _radius;

	// レーザーの先端(ステージ外側)の座標
	VECTOR tmpPos;
	tmpPos.x = cos(util::DegToRad(_roteAngle)) * LASER_LENGTH;
	tmpPos.y = 0.0f;
	tmpPos.z = sin(util::DegToRad(_roteAngle)) * LASER_LENGTH;

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = VAdd(_vPos, tmpPos);
	
	// 向き調整
	float angle = util::DegToRad(-_roteAngle + 90.0f);

	// 位置と向き計算
	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
	SetRotationPlayingEffekseer3DEffect(_playingHandle, 0.0f, angle, 0.0f);

	// 削除処理
	Deletion();
}

/*
 * フレーム処理：描画
 */
void Laser::Render() {
	// 何もしない
}