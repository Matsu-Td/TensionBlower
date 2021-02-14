#pragma once

/**
 * @file Laser.h
 * @brief �{�X�̃��[�U�[�U��
 * 
 * @date 2021-02-14
 */

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