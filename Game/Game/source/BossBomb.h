/**
 * @file   BossBomb.h
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "ShotBase.h"

class BossBomb : public ShotBase {
public:
	/**
	 * @brief �{������
	 * @param pos �{���̔����ʒu
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

private:
	static constexpr int UP_CNT = 24;    // �㏸�J�E���g
	static constexpr int STOP_CNT = 24;  // ��~�J�E���g
};
