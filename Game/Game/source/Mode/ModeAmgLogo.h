/**
 * @file   ModeAmgLogo.h
 * @brief  AMG���S�`�揈��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {
		/**
		 * @brief AMG���S�`�揈��
		 */
		class ModeAmgLogo :public ::mode::ModeBase {
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
			int _bg;      // �w�i
			int _cg;      // �摜
			int _mode;    // �t�F�[�h���䃂�[�h
			int _fadeCnt; // �t�F�[�h�J�E���g 
			int _dispCnt; // �\���J�E���g
			int _alpha;   // �摜�̃��l

			const int MAX_ALPHA    = 255; // �摜���l�̍ő�l
			const int MAX_FADE_CNT = 30;  // �t�F�[�h�J�E���g�ő�l
			const int MAX_DISP_CNT = 90;  // �`��J�E���g�ő�l
			const int LOGO_POS_X   = 460; // ���S�摜X���W
			const int LOGO_POS_Y   = 425; // ���S�摜Y���W
		};
	}
}
