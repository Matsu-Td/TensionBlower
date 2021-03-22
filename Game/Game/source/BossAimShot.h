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
	 * @brief  �_�������e�̐���
	 * @param  pos �����ʒu
	 * @param  shotSpd �e�̈ړ����x
	 * @param  shotAngle �e�̈ړ��p�x�A�����@
	 */
	BossAimShot(VECTOR pos, float shotSpd, float shotAngle);
	~BossAimShot();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();
};
