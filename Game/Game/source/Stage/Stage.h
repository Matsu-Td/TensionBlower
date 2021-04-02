/**
 * @file   Stage.h
 * @brief  ステージクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * ステージクラス
 */
class Stage : public ObjectBase{
public:
	Stage();
	~Stage();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

	/**
	 * フレーム処理：描画
	 */
	void Render() override;
private:
	int _mhMap; // ステージモデル
};
