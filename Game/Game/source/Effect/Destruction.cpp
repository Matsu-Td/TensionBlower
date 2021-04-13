/**
 * @file   Destruction.cpp
 * @brief  �{�X�̎��S�����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "../Mode/ModeGame.h"
#include "../Mode/ModeGameClear.h"
#include "Destruction.h"

Destruction::Destruction(VECTOR pos){

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/destruction/effect_explosion_2.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_gameClearCnt = 200;
}

Destruction::~Destruction() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * �t���[�������F�v�Z
 */
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

/*
 * �t���[�������F�`��
 */
void Destruction::Render(){
	// �������Ȃ�
}
