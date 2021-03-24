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
	 * �{������
	 * @param pos �{���̔����ʒu
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * ������
	 */
	void Initialize() override;

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

private:
	const int UP_CNT = 24;    // �㏸�J�E���g
	const int STOP_CNT = 24;  // ��~�J�E���g
};
