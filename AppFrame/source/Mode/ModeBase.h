/**
 * @file  ModeBase.h
 * @brief ���[�h���N���X
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <string>

namespace mode {

	class ModeServer;

	/**
	 * @brief ���[�h���N���X
	 */
	class ModeBase {
	public:
		ModeBase();
		virtual ~ModeBase();

		/**
		 * @brief  �������A���[�h�Ǘ��T�[�o�[�o�^���Ɉ�x�������s
		 * @return �����̐���
		 */
		virtual bool Initialize();

		/**
		 * @brief  ����A���[�h�Ǘ��T�[�o�[����폜���Ɉ�x�������s
		 * @return �����̐���
		 */
		virtual bool Terminate();

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

	public:
		/**
		 * @brief  ���̃��[�h���n�܂��Ă���̃J�E���^�擾
		 * @return �J�E���g��
		 */
		int	GetModeCount() { return _cntMode; }

		/**
		 * @brief ���̃��[�h���n�܂��Ă���̎���(ms)�擾
		 * @param ����(ms)
		 */
		unsigned long GetModeTime() { return _timeMode; }

		/**
		 * @brief �O�t���[������̌o�ߎ���(ms)�擾
		 * @param �o�ߎ���(ms)
		 */
		unsigned long GetStepTime() { return _timeStep; }

		/**
		 * @brief ���t���[����1��Process()���ĂԂ�(�f�t�H���g:1)
		 * @param frame �t���[����
		 */
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }

		/**
		 * @brief ��̌Ăяo���ɉ���Process()���ĂԂ�(�f�t�H���g:1)
		 * @param �J�E���g��(��)
		 */
		void SetCallOfCount(int count) { _callOfCount = count; }

		/**
		 * @brief  ���t���[����1��Process()���ĂԂ��A���̃t���[�������擾
		 * @return �t���[����
		 */
		int GetCallPerFrame() { return _callPerFrame; }

		/**
		 * @brief  1��̌Ăяo���ɉ���Process()���ĂԂ��A���̃J�E���g��(��)���擾
		 * @return �J�E���g��(��)
		 */
		int GetCallOfCount() { return _callOfCount; }


	private:
		friend	ModeServer;
		// ModeServer�p
		std::string	_szName;
		int			_uid;
		int			_layer;

		/**
		 * @brief ���Ԍo�ߏ���
		 * @param timeNow ���݂̎���(ms)
		 */
		void StepTime(unsigned long timeNow);

		/**
		 * @brief �J�E���g��i�߂�
		 */
		void StepCount();

		// ���[�h�������p
		int	_cntMode;	              // �{���[�h�ɓ����Ă���̃J�E���^, 0�X�^�[�g
		unsigned long _timeMode;      // �{���[�h�ɓ����Ă���̎���(ms)
		unsigned long _timeStep;      // �O�t���[������̌o�ߎ���(ms)
		unsigned long _timeModeBase;  // ���̃��[�h���n�܂�������(ms)
		unsigned long _timePauseBase; // �|�[�Y���̃x�[�X����(ms)
		unsigned long _timePauseStep; // �|�[�Y���̐ώZ����(ms) ���쒆�A���̒l�� _timeMode �ɗp����
		unsigned long _timeOldFrame;  // �O�t���[���̎���(ms)

		// CallPerFrame / CallOfCount�p
		int	_callPerFrame, _callPerFrame_cnt;
		int	_callOfCount;
	};
}