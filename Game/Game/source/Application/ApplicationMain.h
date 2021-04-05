/**
 * @file   ApplicationMain.h
 * @brief  �v���W�F�N�g�̃��C������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

/**
 * @brief �v���W�F�N�g�̃��C������
 */
class ApplicationMain : public ApplicationBase{
	using base = ApplicationBase;

public:
	/**
	 * @brief ������
	 * @param hInstance WinMain������
	 * @return �����̐���
	 */
	virtual bool Initialize(HINSTANCE hInstance);

	/**
	 * @brief  ���
	 * @return �����̐��� 
	 */
	virtual bool Terminate();

	/**
	 * @brief  ����
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
	 * @brief  �E�B���h�E���[�h�A�t���X�N���[�����[�h�w��
	 * @return true
	 */
	virtual bool AppWindowed() { return true; }

	/**
	 * @brief  �\������E�B���h�E�̉���
	 * @return �T�C�Y
	 */
	virtual int DispSizeW() { return 1920; }

	/**
	 * @brief  �\������E�B���h�E�̏c��
	 * @return �T�C�Y
	 */
	virtual int DispSizeH() { return 1080; }

}; 
