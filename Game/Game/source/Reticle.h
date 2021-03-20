/**
 * @file   Reticle.h
 * @brief  �Ə�����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();
};
