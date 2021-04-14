/**
 * @file   ModePause.h
 * @brief  �|�[�Y���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/27
 */

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief �|�[�Y���[�h�N���X
		 */
		class ModePause : public ModeBase {
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
			int _cg;      // �摜
			int _ui[4];   // UI�摜
			int _menuPos; // �I���ʒu

			const int POS_X = 786; // �摜�`��ʒu�FX���W(����)
			const int POS_Y_UP = 380; // �摜�`��ʒu�FY���W(�㑤)
			const int POS_Y_UNDER = 580; // �摜�`��ʒu�FY���W(����)
		};
	}
}
