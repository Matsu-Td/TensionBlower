#pragma once

/**
 * @file  Reticle.h
 * @brief レチクル処理
 *
 * @date 2021-02-08
 */

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
