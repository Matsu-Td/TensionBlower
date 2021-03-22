
/**
 * @file  ApplicationBase.h
 * @brief �A�v���P�[�V�����x�[�X
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

class ApplicationBase{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }

	/**
	 * @brief  �E�B���h�E�������T�C�Y�w��
	 * @return �T�C�Y
	 */
	virtual int DispSizeW() { return 640; }

	/**
	 * @brief  �E�B���h�E�c�����T�C�Y�w��
	 * @return �T�C�Y
	 */
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _pInstance; }

	/**
	 * @brief  �L�[���͏��擾
	 * @return �L�[���͏��
	 */
	virtual int GetKey() { return _gKey; }

	/**
	 * @brief  �L�[�̃g���K���擾
	 * @return �L�[�̃g���K���
	 */
	virtual int GetTrg() { return _gTrg; }

	/**
	 * @brief �Q�[���I���t���O.
	 * @return _gameEnd �Q�[���I���t���O
	 */
	bool GameEndFlag() { return _gameEnd; }

	/**
	 * @brief �Q�[���I���t���O�𗧂Ă�
	 */
	void GameEnd() { _gameEnd = true; }

protected:
	static	ApplicationBase	*_pInstance;

	std::unique_ptr<ModeServer> _serverMode;

	int	 _gKey;              // �L�[���͂̏��
	int  _gTrg;              // �L�[���͂̃g���K���
	bool _gameEnd = false;   // �Q�[���I���t���O
};
