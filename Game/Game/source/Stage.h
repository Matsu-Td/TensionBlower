/**
 * @file   Stage.h
 * @brief  �X�e�[�W�`��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class Stage : public ObjectBase{
public:
	Stage();
	~Stage();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();
private:
	int _mhMap; // �X�e�[�W���f��
};
