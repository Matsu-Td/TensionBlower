/**
 * @file   ModeGameOver.h
 * @brief  �Q�[���I�[�o�[���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeGameOver : public ModeBase{
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
	int	_cg[2];	// �摜

	static constexpr int POS_Y = 390;  // �摜�`��ʒu�FY���W
};
