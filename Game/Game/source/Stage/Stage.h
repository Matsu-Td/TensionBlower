/**
 * @file   Stage.h
 * @brief  �X�e�[�W�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * �X�e�[�W�N���X
 */
class Stage : public ObjectBase{
public:
	Stage();
	~Stage();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

	/**
	 * �t���[�������F�`��
	 */
	void Render() override;
private:
	int _mhMap; // �X�e�[�W���f��
};
