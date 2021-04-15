/**
 * @file   Destruction.h
 * @brief  �{�X�̎��S�����G�t�F�N�g�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace effect {

		/**
		 * @brief �{�X�̎��S�����G�t�F�N�g�N���X
		 */
		class Destruction : public ObjectBase {
		public:
			/**
			 * @brief �{�X�̎��S�G�t�F�N�g����
			 * @param pos �G�t�F�N�g�����ʒu
			 */
			Destruction(VECTOR pos);
			~Destruction();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::DESTRUCTION; }

			/**
			 * @brief �t���[�������F�v�Z
			 */
			void Process() override;

			/**
			 * @brief �t���[�������F�`��
			 */
			void Render() override;

		private:
			int _gameClearCnt;  // �Q�[���N���A�\���܂ł̃J�E���g
			int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
			int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
		};
	}
}