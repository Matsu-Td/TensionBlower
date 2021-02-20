#pragma once

/**
 * @file ModeServer.h
 * @brief ���[�h�Ǘ��T�[�o�[
 * 
 * @date 2020-12-18
 */

#include <list>
#include "ModeBase.h"

class ModeServer{
	typedef	std::list<ModeBase*> lstModeBase;

public:
	ModeServer();
	virtual	~ModeServer();
	static ModeServer * _pInstance;
	static ModeServer*GetInstance() { return (ModeServer*)_pInstance; }

	int Add(ModeBase *mode, int layer, const char *name);		// �o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�
	int Del(ModeBase *mode);		// �폜�\��
	ModeBase *Get(int uid);
	ModeBase *Get(const char *name);
	int GetId(ModeBase* mode);
	int GetId(const char *name);
	const char *GetName(ModeBase* mode);
	const char *GetName(int uid);
	void Clear();
	int	LayerTop() { return INT32_MAX; }

	static bool modeSort(const ModeBase *x, const ModeBase *y) {
		return x->_layer < y->_layer;
	}

	/**
	 * �v���Z�X���񂷂��߂̏�����
	 */
	int ProcessInit();	

	/**
	 * ���C���[�̏�̕�����Process����
	 */
	int Process();		     

	/**
	 * �v���Z�X���񂵂���̌�n��
	 */
	int ProcessFinish(); 

	/**
	 * �`����񂷂��߂̏�����
	 */
	int RenderInit();

	/**
	 * ���C���[�̉��̕�����Render����
	 */
	int Render();	

	/**
	 * �`����񂵂���̌�n��
	 */
	int RenderFinish();

	/**
	 * ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�̏����͌Ă΂Ȃ�
	 */
	int SkipProcessUnderLayer();

	/**
	 * ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�̕`��͌Ă΂Ȃ�
	 */
	int SkipRenderUnderLayer();

	/**
	 * ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�̎��Ԍo�߂��~�߂�
	 */
	int PauseProcessUnderLayer();

private:
	/**
	 * �폜�Adelete
	 */
	int Release(ModeBase *mode); 

	/**
	 * �폜�\�񂳂�Ă��邩�m�F
	 */
	bool IsDelRegist(ModeBase *mode);

	/**
	 * ���X�g�ɓo�^����Ă��邩�m�F
	 */
	bool IsAdd(ModeBase *mode);	

private:
	lstModeBase	_vMode;		 	// ���[�h���X�g
	int			_uid_count;		// uid�J�E���^
	lstModeBase	_vModeAdd;		// �ǉ��\��
	lstModeBase	_vModeDel;		// �폜�\��

	ModeBase	*_nowMode;		    // ���݌Ăяo�����̃��[�h
	ModeBase	*_skipProcessMode;	// ���̃��[�h��艺��Process���Ă΂Ȃ�
	ModeBase	*_skipRenderMode;	// ���̃��[�h��艺��Render���Ă΂Ȃ�
	ModeBase	*_pauseProcessMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�

};
