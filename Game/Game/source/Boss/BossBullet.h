/**
 * @file   BossBullet.h
 * @brief  �{�X�̒e������
 * 
 * @author matsuo tadahiko
 * @date   2020/12/22
 */

#pragma once

#include "ShotBase.h"

namespace tensionblower {

	namespace boss {

		/**
		 * @brief �{�X�̒e������
		 */
		class BossBullet : public ShotBase {
		public:
			/**
			 * @brief �e���p�e����
			 * @param pos �e�����ʒu
			 * @param shotSpd �e�̈ړ����x
			 * @param shotAngle �e�̈ړ��p�x
			 */
			BossBullet(VECTOR pos, float shotSpd, float shotAngle);
			~BossBullet();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

			/**
			 * @brief �t���[�������F�v�Z
			 */
			void Process() override;

		private:
			/**
			 * @brief �e���Ԃ�����
			 */
			void Repel();

			/**
			 * @brief �����蔻��F�v���C���[�̋ߐڍU��
			 */
			void CollisionToPlayerAttack();
		};
	}
}