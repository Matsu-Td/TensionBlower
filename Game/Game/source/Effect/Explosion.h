/**
 * @file   Explosion.h
 * @brief  �{���U���̔����G�t�F�N�g�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace effect {

		/**
		 * @brief �{���U���̔����G�t�F�N�g�N���X
		 */
		class Explosion : public ObjectBase {
		public:
			/**
			 * @brief �{���U���̔����G�t�F�N�g����
			 * @param pos ���������ʒu
			 * @param repelFlag �e���Ԃ��ꂽ�e���ǂ���
			 */
			Explosion(VECTOR pos, bool repelFlag);
			~Explosion();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

			/**
			 * @brief ������
			 */
			void Initialize() override;

			/**
			 * @brief �t���[�������F�v�Z
			 */
			void Process() override;

			/**
			 * @brief �t���[�������F�`��
			 */
			void Render() override;

		private:
			/**
			 * @brief �e�퓖���蔻��Ăяo��
			 */
			void CollisionCall();

			/**
			 * @brief �{�X�Ƃ̓����蔻��
			 */
			void CollisionToBoss(ObjectBase* obj);

			/**
			 * @brief �v���C���[�Ƃ̓����蔻��
			 */
			void CollisionToPlayer(ObjectBase* obj);

			int _effectCnt;     // �G�t�F�N�g�J�E���g
			int _repelFlag;     // �e���Ԃ��ꂽ�e���ǂ���(true:�e���Ԃ��ꂽ�e)
			int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
			int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

			const int ALL_EFFECT_TIME = 180;   // �G�t�F�N�g���Đ�����
			const float MAX_RADIUS = 10.0f; // �ő唼�a�T�C�Y
		};
	}
}