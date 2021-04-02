/**
 * @file   BossBullet.h
 * @brief  �{�X�̒e������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "ShotBase.h"

class BossBullet : public ShotBase {
public:
	/**
	 * �e���p�e����
	 * @param  pos �e�����ʒu
	 * @param  shotSpd �e�̈ړ�����
	 * @param  shotAngle �e�̈ړ��p�x
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �e���Ԃ�����
	 */
	void Repel();

	/**
	 * �����蔻��
	 */
	void Collision() override;
};