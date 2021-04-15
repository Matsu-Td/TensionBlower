/**
 * @file   ModeResult.h
 * @brief  ���U���g���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief ���U���g���[�h�N���X
		 */
		class ModeResult : public ::mode::ModeBase {
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
			int _cg;          // �摜
			int _timeScore;   // �X�R�A�F�o�ߎ��ԗp
			int _hpScore;     // �X�R�A�F�c��HP�ʗp
			int _repelScore;  // �X�R�A�F���e����
			int _energyScore; // �X�R�A�F���l���G�l���M�[�ʗp
			int _allScore;    // �X�R�A�F���X�R�A(�S�X�R�A�̍��v)

			const int MMSEC2SEC = 1000;          // �~���b�˕b�ϊ��p
			const int MAX_SCORE = 100000;        // �X�R�A�ő�l(�o�ߎ��ԁA�c��HP�ʗp)
			const int TIME_LOWER = 120;           // �o�ߎ��ԃX�R�A���_�X�^�[�g����

			const int TIME_SCORE_PER_ONE = 200; // �o�ߎ��Ԃ̃X�R�A��v�Z�l�F1������
			const int HP_SCORE_PER_ONE = 100; // HP�̃X�R�A��v�Z�l�F1������
			const int REPEL_SCORE_PER_ONE = 3000;// �e���Ԃ��񐔂̊�v�Z�l�F1������
			const int ENERGY_SCORE_PER_ONE = 5;   // ���l���G�l���M�[�̊�v�Z�l�F1������
		};
	}
}
