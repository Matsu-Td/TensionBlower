/**
 * @file   Explosion.cpp
 * @brief  ボム攻撃の爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#include "ModeGame.h"
#include "Explosion.h"

Explosion::Explosion(VECTOR pos) {

	_effectResourceHandle = LoadEffekseerEffect("res/effect/explosion/explosion.efkefc", 1.0f);
	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
	_vPos = pos;

	Initialize();
}

Explosion::~Explosion() {

}

void Explosion::Initialize() {
	_cnt = 0;
}

void Explosion::Process(){

	_cnt++;
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _vPos.x, _vPos.y, _vPos.z);

	if (_cnt >= 180) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}


void Explosion::Render(){
}
