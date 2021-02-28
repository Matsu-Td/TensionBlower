/**
 * @file   Reticle.h
 * @brief  ƒŒƒ`ƒNƒ‹ˆ—
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	void Initialize();
	void Process();
	void Render();
};
