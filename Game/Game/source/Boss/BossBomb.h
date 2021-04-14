/**
 * @file   BossBomb.h
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "ShotBase.h"

namespace tensionblower {

	namespace boss {

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
			/**
			 * @brief �㏸����
			 */
			void StateUp();

			/**
			 * @brief ��~����
			 */
			void StateStop();

			/**
			 * @brief �_������
			 */
			void StateSniper();

			/**
			 * @brief �{���̍폜�A�����G�t�F�N�g����
			 */
			void BombDelete();

			/**
			 * @brief �e�퓖���蔻��Ăяo��
			 */
			void CollisionCall();

			/**
			 * @brief �����蔻��F�v���C���[
			 * @param obj �I�u�W�F�N�g�̃|�C���^
			 */
			void CollisionToPlayer(ObjectBase* obj);

			/**
			 * @brief �����蔻��F�Ə�
			 * @param obj �I�u�W�F�N�g�̃|�C���^
			 */
			void CollisionToReticle(ObjectBase* obj);

			/**
			 * @brief �����蔻��F�{�X
			 * @param obj �I�u�W�F�N�g�̃|�C���^
			 */
			void CollisionToBoss(ObjectBase* obj);

			const int UP_CNT = 24;  // �㏸�J�E���g
			const int STOP_CNT = 24;  // ��~�J�E���g
		};
	}
}