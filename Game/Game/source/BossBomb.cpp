/**
 * @file   BossBomb.cpp
 * @brief  ƒ{ƒX‚Ìƒ{ƒ€UŒ‚ˆ—
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

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_vPos = pos;
}

BossBomb::~BossBomb() {
	MV1DeleteModel(_mh);
}

void BossBomb::Initialize() {

	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;
}

void BossBomb::Process() {

	_shotCnt++;
	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= 24) {
			_state = STATE::STOP;
		}
	}

	if (_state == STATE::STOP) {
		if (_shotCnt >= 48) {
			VECTOR plPos = Player::GetInstance()->GetPos();
			_vTarg = plPos;
			_state = STATE::ATTACK;
		}
	}

	if (_state == STATE::ATTACK) {
		
	}
}

void BossBomb::Render() {
	
	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
	MV1DrawModel(_mh);
}
