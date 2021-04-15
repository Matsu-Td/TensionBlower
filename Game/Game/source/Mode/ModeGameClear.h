/**
 * @file   ModeGameClear.h
 * @brief  �Q�[���N���A���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/01/26
 */

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief �Q�[���N���A���[�h�N���X
		 */
		class ModeGameClear : public ::mode::ModeBase {
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
