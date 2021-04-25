/**
 * @file   ModeGame.h
 * @brief  �Q�[�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Boss/Boss.h"
#include "../Mode/ModePause.h"
#include "../CharaData/CharaData.h"
#include "../Player/PlayerStatus.h"
#include "../Boss/BossStatus.h"

namespace tensionblower {

	namespace mode {

		/**
		 * @brief �Q�[�����[�h�N���X
		 */
		class ModeGame : public ::mode::ModeBase {
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

			/**
			 * @brief  �Q�[�����[�h���擾
			 * @return �Q�[�����[�h�̃C���X�^���X
			 */
			static ModeGame* GetModeGame() {
				return static_cast<mode::ModeGame*>(::mode::ModeServer::GetInstance()->Get("game"));
			}

			camera::Camera     _cam;  // �J����
			object::ObjectServer _objServer;  // �I�u�W�F�N�g�Ǘ��T�[�o�[

			std::unique_ptr<charadata::CharaData> _charaData; // JSON�t�@�C������L�����f�[�^�ǂݍ���

			bool _stopObjProcess;       // �I�u�W�F�N�g�������X�g�b�v

		private:
			/**
			 * @brief ���C�g�̐ݒ�
			 */
			void SetLight();

			/**
			 * @brief ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
			 * @param lightHandle ���C�g�n���h��
			 */
			void SetLightColorHandle(int lightHandle);

			player::PlayerStatus _playerStatus;  // �v���C���[�̃X�e�[�^�X
			boss::BossStatus     _bossStatus;    // �{�X�̃X�e�[�^�X
		};
	}
}
