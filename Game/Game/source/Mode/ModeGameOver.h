/**
 * @file   ModeGameOver.h
 * @brief  �Q�[���I�[�o�[���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appframe.h"

class ModeGameOver : public ModeBase{
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
	int	_cg[2];	// �摜

	const int POS_Y = 390;  // �摜�`��ʒu�FY���W
};
