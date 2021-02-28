/**
 * @file   Laser.h
 * @brief  �{�X�̃��[�U�[�U��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class Laser : public ObjectBase{
public:
	Laser();
	~Laser();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::LASER; }

	void Initialize();
	void Process();
	void Render();
};