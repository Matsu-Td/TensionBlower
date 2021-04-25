/**
 * @file   Reticle.h
 * @brief  �v���C���[�Ə�����
 * 
 * @author matsuo tadahiko
 * @date   2021/01/14
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

namespace tensionblower {

	namespace player {
		/**
		 * @brief �v���C���[�Ə�����
		 */
		class Reticle : public object::ObjectBase {
		public:
			Reticle();
			~Reticle();

			OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

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
			 * @brief �ړ�����
			 */
			void Move();

			/**
			 * @brief �摜����ʊO�ɏo��̂�h��
			 */
			void PreventOffScreen();

			/**
			 * @brief �폜����
			 */
			void Deletion();
		};
	}
}
