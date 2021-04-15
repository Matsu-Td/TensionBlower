/**
 * @file   ModeCredit.h
 * @brief  �N���W�b�g���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/01/19
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief �N���W�b�g���[�h�N���X
		 */
		class ModeCredit : public ::mode::ModeBase {
			using base = ModeBase;

		public:
			/**
			 * @brief  ������
			 * @return �����̐���
			 */
			bool Initialize() override;

			/**
			 * @brief  ���
			 * @return �����̐���
			 */
			bool Terminate() override;

			/**
			 * @brief  �t���[�������F�v�Z
			 * @return �����̐���
			 */
			bool Process() override;

			/**
			 * @brief  �t���[�������F�`��
			 * @return �����̐���
			 */
			bool Render() override;

		private:
			int _cg;  // �摜
		};
	}
}
