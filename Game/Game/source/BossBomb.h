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
	 * @brief ボム生成
	 * @param pos ボムの発生位置
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

private:
	static constexpr int UP_CNT = 24;    // 上昇カウント
	static constexpr int STOP_CNT = 24;  // 停止カウント
};
