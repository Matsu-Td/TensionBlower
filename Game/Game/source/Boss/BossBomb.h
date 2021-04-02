/**
 * @file   BossBomb.h
 * @brief  ボスのボム攻撃処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "ShotBase.h"

class BossBomb : public ShotBase {
public:
	/**
	 * ボム生成
	 * @param pos ボムの発生位置
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * 初期化
	 */
	void Initialize() override;

	/**
	 * フレーム処理：計算
	 */
	void Process() override;

private:
	const int UP_CNT = 24;    // 上昇カウント
	const int STOP_CNT = 24;  // 停止カウント
};
