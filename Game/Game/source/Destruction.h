/**
 * @file   Destruction.h
 * @brief  ボスの死亡爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */
#pragma once

#include "appframe.h"

class Destruction : public ObjectBase{
public:
	Destruction(VECTOR pos);
	~Destruction();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::DESTRUCTION; }

	void Process();
	void Render();

private:
	int _gameClearCnt; // ゲームクリア表示までのカウント

	int	_effectHandle;  // エフェクトファイルをロードするハンドル
	int	_playingHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの
};
