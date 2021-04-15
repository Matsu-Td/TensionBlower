/**
 * @file  ApplicationBase.h
 * @brief �A�v���P�[�V�������N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include "EffekseerForDXLib.h"

namespace appframe {

	/**
	 * @brief �A�v���P�[�V�������N���X
	 */
	class ApplicationBase {
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		/**
		 * @brief ������
		 * @param hInstance WinMain�֐��̑�����
		 * @return �����̐���
		 */
		virtual bool Initialize(HINSTANCE hInstance);

		/**
		 * @brief  ���
		 * @return �����̐���
		 */
		virtual bool Terminate();

		/**
		 * @brief  �t���[�������F����
		 * @return �����̐���
		 */
		virtual bool Input();

		/**
		 * @brief  �t���[�������F�v�Z
		 * @return �����̐���
		 */
		virtual bool Process();

		/**
		 * @brief  �t���[�������F�`��
		 * @return �����̐���
		 */
		virtual bool Render();

		/**
		 * @brief  �E�B���h�E���[�h�A�t���X�N���[�����[�h�̐ݒ���s��
		 * @return true
		 */
		virtual bool AppWindowed() { return true; }

		/**
		 * @brief  �\������E�B���h�E�̉���
		 * @return �T�C�Y
		 */
		virtual int DispSizeW() { return 640; }

		/**
		 * @brief  �\������E�B���h�E�̏c��
		 * @return �T�C�Y
		 */
		virtual int DispSizeH() { return 480; }

		/**
		 * @brief  �C���X�^���X���擾
		 * @return ApplicationBase�̃C���X�^���X
		 */
		static	ApplicationBase* GetInstance() { return _pInstance; }

		/**
		 * @brief  �L�[���͏��擾
		 * @return �L�[���͏��
		 */
		virtual int GetKey() { return _key; }

		/**
		 * @brief  �L�[�̃g���K���擾
		 * @return �L�[�̃g���K���
		 */
		virtual int GetKeyTrg() { return _keyTrg; }

		/**
		 * @brief  DINPUT�R���g���[���[���͏��擾
		 * @return DINPUT�R���g���[���[���͏��
		 */
		virtual DINPUT_JOYSTATE GetDInputState() { return _dInput; }

		/**
		 * @brief  �Q�[���I���t���O��Ԃ�
		 * @return �Q�[���I���t���O
		 */
		bool GameEndFlag() const { return _gameEnd; }

		/**
		 * @brief �Q�[���I���t���O�𗧂Ă�
		 */
		void IsGameEnd() { _gameEnd = true; }

	protected:
		static	ApplicationBase* _pInstance;

		std::unique_ptr<mode::ModeServer> _serverMode;

		int	 _key;                // �L�[���͏��
		int  _keyTrg;             // �L�[���͂̃g���K���
		DINPUT_JOYSTATE _dInput;  // DINPUT�R���g���[���[�̓��͏�� 
		bool _gameEnd = false;    // �Q�[���I���t���O
	};
}