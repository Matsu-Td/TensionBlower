/**
 * @file   BossBullet.h
 * @brief  ƒ{ƒX‚Ì’e–‹ˆ—
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "ShotBase.h"

class BossBullet : public ShotBase {
public:
	/**
	 * ’e–‹—p’e¶¬
	 * @param  pos ’e¶¬ˆÊ’u
	 * @param  shotSpd ’e‚ÌˆÚ“®ˆ—
	 * @param  shotAngle ’e‚ÌˆÚ“®Šp“x
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * ƒtƒŒ[ƒ€ˆ—FŒvZ
	 */
	void Process() override;

	/**
	 * ’e‚«•Ô‚µˆ—
	 */
	void Repel();

	/**
	 * “–‚½‚è”»’è
	 */
	void Collision() override;
};