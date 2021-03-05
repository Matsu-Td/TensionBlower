/**
 * @file   Explosion.h
 * @brief  ボム攻撃の爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once
#include "appframe.h"

class Explosion : public ObjectBase{
public:
	Explosion(VECTOR pos);
	~Explosion();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

	void Initialize();
	void Process();
	void Render();

private:
	int _cnt;
	int	_effectResourceHandle;  // エフェクトファイルをロードするハンドル
	int	_playingEffectHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの
};
