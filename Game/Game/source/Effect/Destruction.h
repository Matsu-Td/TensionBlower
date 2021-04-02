/**
 * @file   Destruction.h
 * @brief  �{�X�̎��S�����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */
#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

class Destruction : public ObjectBase{
public:
	/**
	 * �{�X�̎��S�G�t�F�N�g����
	 * @param pos �G�t�F�N�g�����ʒu
	 */
	Destruction(VECTOR pos);
	~Destruction();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::DESTRUCTION; }

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �t���[�������F�`��
	 */
	void Render() override;

private:
	int _gameClearCnt;  // �Q�[���N���A�\���܂ł̃J�E���g
	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
};
