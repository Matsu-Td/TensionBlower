/**
 * @file   Stage.h
 * @brief  ステージ描画
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
	 * @brief フレーム処理：描画
	 */
	void Render();
private:
	int _mhMap; // ステージモデル
};
