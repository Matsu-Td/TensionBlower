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
	 * @brief  �e���p�e����
	 * @param  pos �e�����ʒu
	 * @param  shotSpd �e�̈ړ�����
	 * @param  shotAngle �e�̈ړ��p�x
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

	/**
	 * @brief �e���Ԃ�����
	 */
	void Repel();

	/**
	 * @brief �����蔻��
	 */
	void Collision();


};