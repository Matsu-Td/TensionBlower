/**
 * @file   ModeGameStart.h
 * @brief  MISSION START�摜�`�揈��
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief MISSION START�摜�`�揈��
		 */
		class ModeGameStart : public ::mode::ModeBase {
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
			int _cg[2];   // �摜

			const int POS_Y = 390;  // �摜�`��ʒu�FY���W
		};
	}
}
