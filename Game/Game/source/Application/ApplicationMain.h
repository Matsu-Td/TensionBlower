/**
 * @file   ApplicationMain.h
 * @brief  �v���W�F�N�g�̃��C������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

/**
 * �v���W�F�N�g�̃��C������
 */
class ApplicationMain : public ApplicationBase{
	using base = ApplicationBase;

public:
	/**
	 * ������
	 * @param hInstance WinMain������
	 * @return �����̐���
	 */
	virtual bool Initialize(HINSTANCE hInstance);

	/**
	 * ���
	 * @return �����̐��� 
	 */
	virtual bool Terminate();

	/**
	 * ����
	 * @return �����̐���
	 */
	virtual bool Input();

	/**
	 * �t���[�������F�v�Z
	 * @return 
	 */
	virtual bool Process();

	/**
	 * �t���[�������F�`��
	 * @return 
	 */
	virtual bool Render();

	/**
	 * 
	 * @return 
	 */
	virtual bool AppWindowed() { return true; }

	/**
	 * �\������E�B���h�E�̉���
	 * @return �T�C�Y
	 */
	virtual int DispSizeW() { return 1920; }

	/**
	 * �\������E�B���h�E�̏c��
	 * @return �T�C�Y
	 */
	virtual int DispSizeH() { return 1080; }

}; 
