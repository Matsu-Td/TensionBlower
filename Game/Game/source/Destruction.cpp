/**
 * @file   Destruction.cpp
 * @brief  �{�X�̎��S�����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "ModeGame.h"
#include "ModeGameClear.h"
#include "Destruction.h"

Destruction::Destruction(VECTOR pos){

	_effectHandle = LoadEffekseerEffect("res/effect/destruction/effect_explosion_2.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_gameClearCnt = 200;
}

Destruction::~Destruction() {
	DeleteEffekseerEffect(_effectHandle);
	StopEffekseer3DEffect(_playingHandle);
}

void Destruction::Process(){

	_gameClearCnt--;

	// �Q�[���N���A�J�E���g�u0�v�ŃG�t�F�N�g�폜���A�Q�[���N���A�Ɉڍs
	if (_gameClearCnt <= 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
		ModeGameClear* modeGameClear = NEW ModeGameClear();
		ModeServer::GetInstance()->Add(modeGameClear, 2, "clear");
	}
	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
}

void Destruction::Render(){

}
