/**
 * @file   ModePause.h
 * @brief  �|�[�Y���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModePause : public ModeBase{
	using base = ModeBase;

public:
	/**
	 * ������
	 * @return �����̐���
	 */
	bool Initialize() override;

	/**
	 * ���
	 * @return �����̐���
	 */
	bool Terminate() override;

	/**
	 * �t���[�������F�v�Z
	 * @return �����̐���
	 */
	bool Process() override;

	/**
	 * �t���[�������F�`��
	 * @return �����̐���
	 */
	bool Render() override;

private:
	int _cg;      // �摜
	int _ui[4];   // UI�摜
	int _menuPos; // �I���ʒu
};