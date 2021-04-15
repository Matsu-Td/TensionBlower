/**
 * @file  ModeServer.h
 * @brief ���[�h�Ǘ��N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include <list>
#include "ModeBase.h"

namespace mode {

	/**
	 * @brief ���[�h�Ǘ��N���X
	 */
	class ModeServer {
		using lstModeBase = std::list<ModeBase*>;

	public:
		ModeServer();
		virtual	~ModeServer();
		static ModeServer* _pInstance;
		static ModeServer* GetInstance() { return (ModeServer*)_pInstance; }

		/**
		 * @brief ���[�h�T�[�o�[�ɐV���ȃ��[�h��ǉ��\�񂷂�A�ǉ����s��1�t���[����
		 * @param mode  �ǉ����郂�[�h
		 * @param layer �\�����郌�C���[
		 * @param name  ���[�h�̖��O
		 * @return �ǉ��������[�h��ID
		 */
		int Add(ModeBase* mode, int layer, const char* name);		// �o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�

		/**
		 * @brief �o�^���Ă��郂�[�h�̍폜�\�������A�폜���s��1�t���[����
		 * @param �폜���郂�[�h
		 * @return 0
		 */
		int Del(ModeBase* mode);

		/**
		 * @brief uid����w�肵�����[�h���擾
		 * @param uid ���[�h��ID
		 * @return �w�肵��ID�̃��[�h
		 */
		ModeBase* Get(int uid);

		/**
		 * @brief ���[�h�̖��O����w�肵�����[�h���擾
		 * @param name ���[�h�̖��O
		 * @return �w�肵�����O�̃��[�h
		 */
		ModeBase* Get(const char* name);

		/**
		 * @brief ���[�h����ID���擾
		 * @param mode ���[�h�̃|�C���^
		 * @return �w�肵�����[�h��ID�@�o�^����Ă��Ȃ��ꍇ�� 0 ��Ԃ�
		 */
		int GetId(ModeBase* mode);

		/**
		 * @brief ���[�h�̖��O����ID���擾
		 * @param name ���[�h�̖��O
		 * @return �w�肵�����[�h��ID�@�o�^����Ă��Ȃ��ꍇ�� 0 ���Ԃ�
		 */
		int GetId(const char* name);

		/**
		 * @brief ���[�h�̃|�C���^���烂�[�h�̖��O���擾
		 * @param mode ���[�h�̃|�C���^
		 * @return �w�肵�����[�h�̖��O
		 */
		const char* GetName(ModeBase* mode);

		/**
		 * @brief ID���烂�[�h�̖��O���擾
		 * @param uid ���[�h��ID
		 * @return �w�肵�����[�h�̖��O
		 */
		const char* GetName(int uid);

		/**
		 * @brief �o�^���Ă������[�h�����[�h�T�[�o�[����S�č폜�A���������
		 */
		void Clear();

		/**
		 * @brief  ���C���[���ő�l�Ɏw��
		 * @return int32_t �̍ő�l
		 */
		int	LayerTop() { return INT32_MAX; }

		/**
		 * @brief ���C���[�̏��Ƀ\�[�g���s��
		 * @param x ���[�h1
		 * @param y ���[�h2
		 * @return x �� y �̃��C���[��菬�������A���̌���
		 */
		static bool modeSort(const ModeBase* x, const ModeBase* y) {
			return x->_layer < y->_layer;
		}

		/**
		 * @brief  �v���Z�X���񂷂��߂̏�����
		 * @return 0
		 */
		int ProcessInit();

		/**
		 * @brief  ���C���[�̏�̕�����Process����
		 * @return 0
		 */
		int Process();

		/**
		 * @brief  �v���Z�X���񂵂���̌�n��
		 * @return 0
		 */
		int ProcessFinish();

		/**
		 * @brief  �`����񂷂��߂̏�����
		 * @return 0
		 */
		int RenderInit();

		/**
		 * @brief  ���C���[�̉��̕�����Render����
		 * @return 0
		 */
		int Render();

		/**
		 * @brief  �`����񂵂���̌�n��
		 * @return 0
		 */
		int RenderFinish();

		/**
		 * @brief  ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�͏����͌Ă΂Ȃ�
		 * @return 0
		 */
		int SkipProcessUnderLayer();

		/**
		 * @brief  ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�͕`��͌Ă΂Ȃ�
		 * @return 0
		 */
		int SkipRenderUnderLayer();

		/**
		 * @brief  ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�͎��Ԍo�߂��~�߂�
		 * @return 0
		 */
		int PauseProcessUnderLayer();

	private:
		/**
		 * @brief �w�肵�����[�h�����[�h�T�[�o�[����폜�A���������
		 * @param mode ���[�h�̃|�C���^
		 * @return 1
		 */
		int Release(ModeBase* mode);

		/**
		 * @brief �w�肵�����[�h���폜�\�񂳂�Ă��邩�m�F
		 * @param mode ���[�h�̃|�C���^
		 * @return true:�폜�\�񂠂�Afalse:�폜�\��Ȃ�
		 */
		bool IsDelRegist(ModeBase* mode);

		/**
		 * @brief �w�肵�����[�h�����X�g�ɓo�^�A�o�^�\�񂳂�Ă��邩�m�F
		 * @param mode ���[�h�̃|�C���^
		 * @return true:�o�^����@false:�o�^�Ȃ�
		 */
		bool IsAdd(ModeBase* mode);

	private:
		lstModeBase	_vMode;		 	// ���[�h���X�g
		int			_uid_count;		// uid�J�E���^
		lstModeBase	_vModeAdd;		// �ǉ��\��
		lstModeBase	_vModeDel;		// �폜�\��

		ModeBase* _nowMode;		    // ���݌Ăяo�����̃��[�h
		ModeBase* _skipProcessMode;	// ���̃��[�h��艺��Process���Ă΂Ȃ�
		ModeBase* _skipRenderMode;	// ���̃��[�h��艺��Render���Ă΂Ȃ�
		ModeBase* _pauseProcessMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�
	};
}