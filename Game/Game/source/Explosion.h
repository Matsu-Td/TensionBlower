/**
 * @file   Explosion.h
 * @brief  �{���U���̔����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once
#include "appframe.h"

class Explosion : public ObjectBase{
public:
	Explosion(VECTOR pos);
	~Explosion();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

	void Initialize();
	void Process();
	void Render();

private:
	int _cnt;
	int	_effectResourceHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
};
