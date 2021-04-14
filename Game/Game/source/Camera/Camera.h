/**
 * @file   Camera.h
 * @brief  �J�����N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"

namespace tensionblower {

	namespace camera {

		/**
		 * @brief �J�����N���X
		 */
		class Camera {
		public:
			Camera();
			~Camera();

			/**
			 * @brief ������
			 */
			void Initialize();

			/**
			 * @brief �t���[�������F�v�Z
			 */
			void Process();

			/**
			 * @brief �t���[�������F�`��
			 */
			void Render();

			/**
			 * �C���X�^���X���擾
			 * @return Camera�̃C���X�^���X
			 */
			static Camera* GetInstance() { return _pInstance; }

			/**
			 * @brief ���W�擾
			 * @return ���W
			 */
			VECTOR GetPos() const { return _vPos; }

			/**
			 * @brief  �^�[�Q�b�g���W�擾
			 * @return �^�[�Q�b�g���W
			 */
			VECTOR GetTarg() const { return _vTarg; }

			/**
			 * @brief �J�����̌����Ă���p�x(rad)�擾
			 * @return �J�����̊p�x(rad)
			 */
			float GetRad() const;

			/**
			 * @brief �J�����̏��
			 */
			enum class STATE {
				NORMAL,    // �ʏ���
				MLS_LOCK,  // �}���`���b�N�V�X�e���������(FPS���_)
			};
			STATE _state;  // �J�������

			/**
			 * @brief  �J�����̏�Ԃ��擾
			 * @return �J�����̏��
			 */
			STATE GetState() const { return _state; }

			static Camera* _pInstance;

		private:
			/**
			 * @brief �J�����̈ʒu��ݒ�
			 * @param dis �v���C���[����̋���
			 * @param height �v���C���[����̍���
			 */
			void SetPos(float dis, float height);

			/**
			 * @brief �ʏ��Ԃ̏���
			 */
			void StateNorm();

			/**
			 * @brief �}���`���b�N�I���V�X�e���������̏���
			 */
			void StateMLSLock();

			VECTOR _vPos;    // �ʒu
			VECTOR _vTarg;   // �����_

			struct LOCK_ON { // �\���́F���b�N�I�����
				int x, y;  // �X�N���[�����W
				int cg;    // �摜
			};
			LOCK_ON _lockOn;

			const float NEAR_CLIP = 0.1f;    // ��O�N���b�v����
			const float FAR_CLIP = 5000.0f; // ���N���b�v����
		};
	}
}