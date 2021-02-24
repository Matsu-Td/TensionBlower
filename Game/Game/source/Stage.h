#pragma once

/**
 * @file  Stage.h
 * @brief ステージ描画
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class Stage : public ObjectBase{
public:
	Stage();
	~Stage();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

	void Render();
private:
	int _mhMap;
};
