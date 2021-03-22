/**
 * @file   BossBullet.h
 * @brief  ƒ{ƒX‚Ì’e–‹ˆ—
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "BulletBase.h"

class BossBullet : public BulletBase{
public:
	/**
	 * @brief  ’e–‹—p’e¶¬
	 * @param  pos ’e¶¬ˆÊ’u
	 * @param  shotSpd ’e‚ÌˆÚ“®ˆ—
	 * @param  shotAngle ’e‚ÌˆÚ“®Šp“x
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief ƒtƒŒ[ƒ€ˆ—FŒvZ
	 */
	void Process();

	/**
	 * @brief ’e‚«•Ô‚µˆ—
	 */
	void Repel();

	/**
	 * @brief “–‚½‚è”»’è
	 */
	void Collision();


};