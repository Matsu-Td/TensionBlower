/**
 * @file   BossBomb.h
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "ShotBase.h"

/**
 * @brief �{�X�̃{���U������
 */
class BossBomb : public ShotBase {
public:
	/**
	 * @brief �{������
	 * @param pos �{���̔����ʒu
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

	/**
	 * @brief ������
	 */
	void Initialize() override;

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process() override;

private:
	const int UP_CNT = 24;    // �㏸�J�E���g
	const int STOP_CNT = 24;  // ��~�J�E���g
};
