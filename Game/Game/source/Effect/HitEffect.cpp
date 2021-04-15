/**
 * @file   HitEffect.cpp
 * @brief  �ߐڍU���̃q�b�g�G�t�F�N�g
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "HitEffect.h"
#include "../Mode/ModeGame.h"

using namespace tensionblower::effect;

HitEffect::HitEffect(VECTOR pos) {

	_effectHandle  = resource::ResourceServer::LoadEffekseerEffect("res/effect/hit/hit.efkefc", 1.5f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;

	Initialize();
}

HitEffect::~HitEffect() {
	StopEffekseer3DEffect(_playingHandle);
}

/*
 * ������
 */
void HitEffect::Initialize() {

	_effectCnt = 0;
}

/*
 * �t���[�������F�v�Z
 */
void HitEffect::Process() {

	_effectCnt++;

	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);

	// ���Đ����Ԃ��}������G�t�F�N�g�폜
	if (_effectCnt >= ALL_EFFECT_TIME) {
		mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}
}

/*
 * �t���[�������F�`��
 */
void HitEffect::Render() {
	// �������Ȃ�
}