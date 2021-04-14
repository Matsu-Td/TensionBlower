/**
 * @file   ModeGame.h
 * @brief  �Q�[�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

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
		class ModeGame : public ModeBase {
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

			Camera       _cam;
			ObjectServer _objServer;

			std::unique_ptr<CharaData> _charaData; // JSON�t�@�C������L�����f�[�^�ǂݍ���

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

			PlayerStatus _playerStatus;
			BossStatus   _bossStatus;
		};
	}
}
