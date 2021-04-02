/**
 * @file   Reticle.h
 * @brief  �v���C���[�Ə�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * �v���C���[�Ə�����
 */
class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	/**
	 * ������
	 */
	void Initialize() override;

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �t���[�������F�`��
	 */
	void Render() override;

private:
	const float ANALOG_MIN = 0.3f; // �A�i���O�X�e�B�b�N���͔����̍ŏ��l
};
