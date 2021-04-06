/**
 * @file   Reticle.h
 * @brief  �v���C���[�Ə�����
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * @brief �v���C���[�Ə�����
 */
class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	/**
	 * @brief ������
	 */
	void Initialize() override;

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render() override;

private:
	const float ANALOG_MIN = 0.3f; // �A�i���O�X�e�B�b�N���͔����̍ŏ��l
};
