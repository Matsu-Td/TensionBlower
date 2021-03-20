/**
 * @file   ModePause.h
 * @brief  �|�[�Y���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModePause : public ModeBase{
	typedef ModeBase base;

public:
	/**
	 * @brief  ������
	 * @return �����̐���or���s
	 */
	virtual bool Initialize();

	/**
	 * @brief  ���
	 * @return �����̐���or���s
	 */
	virtual bool Terminate();

	/**
	 * @brief  �t���[�������F�v�Z
	 * @return �����̐���or���s
	 */
	virtual bool Process();

	/**
	 * @brief  �t���[�������F�`��
	 * @return �����̐���or���s
	 */
	virtual bool Render();

protected:
	int _cg;      // �摜
	int _ui[4];   // UI�摜
	int _menuPos; // �I���ʒu
};