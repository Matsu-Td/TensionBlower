/**
 * @file   Laser.cpp
 * @brief  ボスのレーザー攻撃
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Laser.h"
#include "ModeGame.h"
#include "Boss.h"

Laser::Laser(VECTOR pos, float radius, float angle, float roteSpd) {

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/beam/effect_beam.efkefc", 1.0f);
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

/**
 * 初期化
 */
void Laser::Initialize() {

	_r = 5.0f;
	_effectCnt = 240;
	_mlsCnt = 0;
}

/**
 * フレーム処理：計算
 */
void Laser::Process() {

	// カメラの状態を取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	// ボスの状態を取得
	Boss::STATE bsState = Boss::GetInstance()->GetState();

	// ボスがダウンしたらレーザー削除
	if (bsState == Boss::STATE::DOWN) {
		StopEffekseer3DEffect(_playingHandle);
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}

	// マルチロックオンシステム発動中の回転速度を1/100にする
	if (camState == Camera::STATE::MLS_LOCK) {
		_roteAngle += _roteSpd * MLS_SPD;
	}
	else {
		_roteAngle += _roteSpd;
	}

	// レーザー当たり判定の長さ指定
	float length = 125.0f;

	// 発射位置
	_vPos.x = cos(_roteAngle / 180.0f * DX_PI_F) * _radius;
	_vPos.z = sin(_roteAngle / 180.0f * DX_PI_F) * _radius;

	// レーザーの先端(ステージ外側)の座標
	VECTOR tipPos;
	tipPos.x = cos(_roteAngle / 180.0f * DX_PI_F) * length;
	tipPos.y = 0.0f;
	tipPos.z = sin(_roteAngle / 180.0f * DX_PI_F) * length;

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos2 = VAdd(_vPos, tipPos);
	
	// 向き調整
	float angle = (-_roteAngle + 90.0f) / 180.0f * DX_PI_F;

	// 位置と向き計算
	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
	SetRotationPlayingEffekseer3DEffect(_playingHandle, 0.0f, angle, 0.0f);

	_effectCnt--;
	// 再生カウントが「0」になればレーザーを削除する
	if (_effectCnt <= 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
	

}

/**
 * フレーム処理：描画
 */
void Laser::Render() {

}