/**
 * @file   Destruction.h
 * @brief  �{�X�̎��S�����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */
#pragma once

#include "appframe.h"

class Destruction : public ObjectBase{
public:
	Destruction(VECTOR pos);
	~Destruction();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::DESTRUCTION; }

	void Process();
	void Render();

private:
	int _gameClearCnt; // �Q�[���N���A�\���܂ł̃J�E���g

	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
};