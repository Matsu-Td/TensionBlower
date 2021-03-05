/**
 * @file   BossBomb.cpp
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"
#include "Explosion.h"
#include "Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {

}

void BossBomb::Initialize() {

	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;
}

void BossBomb::Process() {

	// 狙撃までのカウント
	_shotCnt++;

	// 上昇処理
	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // カウントリセット
			_state = STATE::STOP;  // 停止状態に移行
		}
	}

	// 停止処理
	if (_state == STATE::STOP) {
		if (_shotCnt >= STOP_CNT) {
			_shotCnt = 0;
			// プレイヤー位置情報取得
			VECTOR plPos = Player::GetInstance()->GetPos();
			plPos.y = 0.0f;          // プレイヤーの足元(ステージ上)をターゲットとする
			_vTarg = plPos;          // プレイヤーをターゲットとする
			_state = STATE::SNIPER;  // 射撃状態に移行
		}
	}

	// 狙撃処理
	if (_state == STATE::SNIPER) {
		// ターゲットに向かってボムを発射する
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, 2.0f);
		_vPos = VAdd(_vPos, targ);
	}

	// ステージ床まで下降したらボムを削除
	if (_vPos.y <= 0.0f) {
		PlaySoundMem(gSound._se["explosion1"], DX_PLAYTYPE_BACK);
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Explosion* explosion = NEW Explosion(_vPos);
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);

	}
}

void BossBomb::Render() {
	
	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
	MV1DrawModel(_mh);

	DrawFormatString(960, 540, GetColor(255, 0, 0), "%d",_state);
}
