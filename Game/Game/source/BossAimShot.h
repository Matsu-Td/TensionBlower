/**
 * @file   BossAimShot.h
 * @brief  �{�X�̑_�������e
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#pragma once
#include "ShotBase.h"

class BossAimShot :public ShotBase {
public:
	/**
	 * �_�������e�̐���
	 * @param  pos �����ʒu
	 * @param  shotSpd �e�̈ړ����x
	 * @param  shotAngle �e�̈ړ��p�x�A�����@
	 */
	BossAimShot(VECTOR pos, float shotSpd, float shotAngle);
	~BossAimShot();

	OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;
};
